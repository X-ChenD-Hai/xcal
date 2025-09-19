#ifndef VIDEO_ENCODER_H
#define VIDEO_ENCODER_H

#include <xcal/public.h>

#include <string>
#include <vector>
#include <xcal/render/core/abs_videocodec.hpp>

extern "C" {
struct AVFormatContext;
struct AVCodecContext;
struct AVStream;
struct AVFrame;
struct AVFrame;
struct SwsContext;
struct AVPacket;
}
namespace xcal::render::codec {

class XCAL_CODEC_API FfmpegCodec : public AbsVideoCodec {
   public:
    FfmpegCodec(const std::string& filename, int width, int height,
                int frame_rate);
    ~FfmpegCodec();

    bool_t open() override;
    bool_t append_frame(const std::vector<char>& rgba_data) override;
    bool_t finish() override;

    int encoded_frames() const { return encoded_frames_; }

   private:
    bool encode_frame(AVFrame* frame);
    bool write_packet(AVPacket* packet);
    bool setup_scaler();

    int encoded_frames_;

    // FFmpeg相关资源
    AVFormatContext* format_ctx_;
    AVCodecContext* codec_ctx_;
    AVStream* video_stream_;
    AVFrame* frame_;
    AVFrame* rgba_frame_;
    SwsContext* sws_ctx_;

    bool initialized_;
    bool finished_;
};
}  // namespace xcal::render::codec

#endif  // VIDEO_ENCODER_H