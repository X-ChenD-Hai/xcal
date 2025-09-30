#include <cmath>
#include <codec/ffmpeg/ffmpegcodec.hpp>
#include <iostream>
#include <vector>

using namespace xcal::render::codec;
// 生成简单的颜色渐变测试帧
std::vector<char> generateGradientFrame(int width, int height, int frame_num) {
    std::vector<char> frame_data(width * height * 4);

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int index = (y * width + x) * 4;

            // 创建颜色渐变效果
            float time = frame_num / 30.0f;  // 每30帧一个周期

            // RGB颜色计算
            frame_data[index] =
                static_cast<char>(128 + 127 * sin(x * 0.1f + time));  // R
            frame_data[index + 1] =
                static_cast<char>(128 + 127 * sin(y * 0.1f + time));  // G
            frame_data[index + 2] = static_cast<char>(
                128 + 127 * sin((x + y) * 0.05f + time));  // B
            frame_data[index + 3] = 255u;                  // Alpha通道
        }
    }

    return frame_data;
}

int main() {
    const int width = 1280;
    const int height = 720;
    const int frame_rate = 30;
    const int total_frames = 300;  // 10秒视频

    std::cout << "Creating gradient animation video..." << std::endl;

    try {
        FfmpegCodec encoder("gradient_video.mp4", width, height, frame_rate);

        for (int i = 0; i < total_frames; i++) {
            auto frame_data = generateGradientFrame(width, height, i);

            if (!encoder.append_frame(frame_data)) {
                std::cerr << "Failed to append frame " << i << std::endl;
                break;
            }

            // 显示进度
            if (i % 30 == 0) {
                float progress = (i * 100.0f) / total_frames;
                std::cout << "Progress: " << progress << "% (" << i << "/"
                          << total_frames << " frames)" << std::endl;
            }
        }

        if (!encoder.finish()) {
            std::cerr << "Failed to finish encoding" << std::endl;
            return 1;
        }

        std::cout << "Video created successfully: gradient_video.mp4"
                  << std::endl;
        std::cout << "Total frames encoded: " << encoder.encoded_frames()
                  << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}