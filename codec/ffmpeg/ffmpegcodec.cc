#include "ffmpegcodec.hpp"

#include <xcal/public.h>

extern "C" {
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libavutil/imgutils.h>
#include <libavutil/opt.h>
#include <libswscale/swscale.h>
}
#include <ffmpegcodec.hpp>
#include <iostream>

xcal::render::codec::FfmpegCodec::FfmpegCodec(const std::string& filename,
                                              int width, int height,
                                              int frame_rate)
    : AbsVideoCodec(filename, width, height, frame_rate),
      encoded_frames_(0),
      format_ctx_(nullptr),
      codec_ctx_(nullptr),
      video_stream_(nullptr),
      frame_(nullptr),
      rgba_frame_(nullptr),
      sws_ctx_(nullptr),
      initialized_(false),
      finished_(false) {}

xcal::render::codec::FfmpegCodec::~FfmpegCodec() {
    if (!finished_) {
        finish();
    }

    // 清理资源
    if (sws_ctx_) {
        sws_freeContext(sws_ctx_);
        sws_ctx_ = nullptr;
    }

    if (frame_) {
        av_frame_free(&frame_);
    }

    if (rgba_frame_) {
        av_frame_free(&rgba_frame_);
    }

    if (codec_ctx_) {
        avcodec_free_context(&codec_ctx_);
    }

    if (format_ctx_) {
        if (format_ctx_->pb) {
            avio_closep(&format_ctx_->pb);
        }
        avformat_free_context(format_ctx_);
    }
}

xcal::bool_t xcal::render::codec::FfmpegCodec::open() {
    if (initialized_) {
        return true;
    }

    avformat_network_init();

    // 创建输出格式上下文
    int ret = avformat_alloc_output_context2(&format_ctx_, nullptr, nullptr,
                                             filename().c_str());
    if (ret < 0) {
        std::cerr << "Could not create output context: " << ret << std::endl;
        return false;
    }

    // 查找编码器
    const AVCodec* codec = avcodec_find_encoder(AV_CODEC_ID_H264);
    if (!codec) {
        std::cerr << "H.264 encoder not found" << std::endl;
        return false;
    }

    // 创建视频流
    video_stream_ = avformat_new_stream(format_ctx_, codec);
    if (!video_stream_) {
        std::cerr << "Could not create video stream" << std::endl;
        return false;
    }

    // 配置编码器上下文
    codec_ctx_ = avcodec_alloc_context3(codec);
    if (!codec_ctx_) {
        std::cerr << "Could not allocate codec context" << std::endl;
        return false;
    }

    codec_ctx_->codec_id = AV_CODEC_ID_H264;
    codec_ctx_->bit_rate = 4000000;  // 4 Mbps
    codec_ctx_->width = width();
    codec_ctx_->height = height();
    codec_ctx_->time_base = {1, frame_rate()};
    codec_ctx_->framerate = {frame_rate(), 1};
    codec_ctx_->gop_size = 12;
    codec_ctx_->max_b_frames = 2;
    codec_ctx_->pix_fmt = AV_PIX_FMT_YUV420P;

    // 设置编码器预设
    av_opt_set(codec_ctx_->priv_data, "preset", "medium", 0);
    av_opt_set(codec_ctx_->priv_data, "crf", "23", 0);

    // 打开编码器
    ret = avcodec_open2(codec_ctx_, codec, nullptr);
    if (ret < 0) {
        std::cerr << "Could not open codec: " << ret << std::endl;
        return false;
    }

    // 将编码器参数复制到流中
    ret = avcodec_parameters_from_context(video_stream_->codecpar, codec_ctx_);
    if (ret < 0) {
        std::cerr << "Could not copy codec parameters: " << ret << std::endl;
        return false;
    }

    video_stream_->time_base = codec_ctx_->time_base;

    // 打开输出文件
    if (!(format_ctx_->oformat->flags & AVFMT_NOFILE)) {
        ret = avio_open(&format_ctx_->pb, filename().c_str(), AVIO_FLAG_WRITE);
        if (ret < 0) {
            std::cerr << "Could not open output file: " << ret << std::endl;
            return false;
        }
    }

    // 写入文件头
    ret = avformat_write_header(format_ctx_, nullptr);
    if (ret < 0) {
        std::cerr << "Error writing header: " << ret << std::endl;
        return false;
    }

    // 创建YUV帧
    frame_ = av_frame_alloc();
    if (!frame_) {
        std::cerr << "Could not allocate video frame" << std::endl;
        return false;
    }

    frame_->format = codec_ctx_->pix_fmt;
    frame_->width = codec_ctx_->width;
    frame_->height = codec_ctx_->height;

    ret = av_frame_get_buffer(frame_, 0);
    if (ret < 0) {
        std::cerr << "Could not allocate frame data: " << ret << std::endl;
        return false;
    }

    // 创建RGBA帧
    rgba_frame_ = av_frame_alloc();
    if (!rgba_frame_) {
        std::cerr << "Could not allocate RGBA frame" << std::endl;
        return false;
    }

    rgba_frame_->format = AV_PIX_FMT_RGBA;
    rgba_frame_->width = width();
    rgba_frame_->height = height();

    ret = av_frame_get_buffer(rgba_frame_, 0);
    if (ret < 0) {
        std::cerr << "Could not allocate RGBA frame data: " << ret << std::endl;
        return false;
    }

    // 设置图像缩放转换器
    if (!setup_scaler()) {
        std::cerr << "Could not setup scaler" << std::endl;
        return false;
    }

    initialized_ = true;
    std::cout << "Video encoder initialized successfully" << std::endl;
    return true;
}

bool xcal::render::codec::FfmpegCodec::setup_scaler() {
    sws_ctx_ = sws_getContext(width(), height(), AV_PIX_FMT_RGBA, width(),
                              height(), AV_PIX_FMT_YUV420P, SWS_BILINEAR,
                              nullptr, nullptr, nullptr);

    return sws_ctx_ != nullptr;
}

bool xcal::render::codec::FfmpegCodec::append_frame(
    const std::vector<char>& rgba_data) {
    if (!initialized_ && !open()) {
        return false;
    }

    if (finished_) {
        std::cerr << "Encoder already finished" << std::endl;
        return false;
    }

    if (rgba_data.size() != static_cast<size_t>(width() * height() * 4)) {
        std::cerr << "Invalid RGBA data size. Expected: "
                  << width() * height() * 4 << ", Got: " << rgba_data.size()
                  << std::endl;
        return false;
    }

    // 复制RGBA数据到帧中
    for (int y = 0; y < height(); y++) {
        memcpy(rgba_frame_->data[0] + y * rgba_frame_->linesize[0],
               rgba_data.data() + y * width() * 4, width() * 4);
    }

    rgba_frame_->pts = encoded_frames_;

    // 转换RGBA到YUV
    sws_scale(sws_ctx_, rgba_frame_->data, rgba_frame_->linesize, 0, height(),
              frame_->data, frame_->linesize);

    frame_->pts = encoded_frames_;

    // 编码帧
    if (!encode_frame(frame_)) {
        return false;
    }

    encoded_frames_++;
    return true;
}

xcal::bool_t xcal::render::codec::FfmpegCodec::encode_frame(AVFrame* frame) {
    int ret = avcodec_send_frame(codec_ctx_, frame);
    if (ret < 0) {
        std::cerr << "Error sending frame to encoder: " << ret << std::endl;
        return false;
    }

    // 使用 av_packet_alloc 而不是已弃用的 av_init_packet
    AVPacket* packet = av_packet_alloc();
    if (!packet) {
        std::cerr << "Could not allocate packet" << std::endl;
        return false;
    }

    while (ret >= 0) {
        ret = avcodec_receive_packet(codec_ctx_, packet);
        if (ret == AVERROR(EAGAIN) || ret == AVERROR_EOF) {
            break;
        } else if (ret < 0) {
            std::cerr << "Error encoding frame: " << ret << std::endl;
            av_packet_free(&packet);
            return false;
        }

        // 调整时间戳
        av_packet_rescale_ts(packet, codec_ctx_->time_base,
                             video_stream_->time_base);
        packet->stream_index = video_stream_->index;

        // 写入包
        ret = av_interleaved_write_frame(format_ctx_, packet);
        if (ret < 0) {
            std::cerr << "Error writing packet: " << ret << std::endl;
            av_packet_free(&packet);
            return false;
        }

        av_packet_unref(packet);
    }

    av_packet_free(&packet);
    return true;
}

xcal::bool_t xcal::render::codec::FfmpegCodec::finish() {
    if (finished_) {
        return true;
    }

    if (!initialized_) {
        std::cerr << "Encoder not initialized" << std::endl;
        return false;
    }

    // 刷新编码器
    encode_frame(nullptr);

    // 写入文件尾
    int ret = av_write_trailer(format_ctx_);
    if (ret < 0) {
        std::cerr << "Error writing trailer: " << ret << std::endl;
        return false;
    }

    // 关闭输出文件
    if (format_ctx_ && !(format_ctx_->oformat->flags & AVFMT_NOFILE)) {
        avio_closep(&format_ctx_->pb);
    }

    finished_ = true;
    std::cout << "Encoding completed. Total frames: " << encoded_frames_
              << std::endl;
    return true;
}