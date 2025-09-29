/**
 * @file fpscontroler.hpp
 * @author X_Chen D_Hai (illuminatestar@foxmail.com)
 * @brief
 * @version 0.1
 * @date 2025-09-28
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once
#include <xcal/camera/core/abs_camera.hpp>
#include <xcal/property/scalar.hpp>
namespace xcal::camera {

class FpsCameraControler {
   public:
    enum class Direction : uint8_t {
        FORWARD = 1,
        BACKWARD,
        LEFT,
        RIGHT,
        UP,
        DOWN,
    };

   private:
    AbsCamera* camera_{nullptr};

    float_t yaw_{270.0f};
    float_t pitch_{0.0f};

   public:
    explicit FpsCameraControler(AbsCamera* camera) : camera_(camera) {}

   public:
    void set_camera(AbsCamera* camera) {
        camera_ = camera;
        yaw_ = 90.0f;
        pitch_ = 0.0f;
    }
    xcmath::vec3<float_t> forward() const {
        return (camera_->target().value() - camera_->position().value())
            .normalize();
    }
    xcmath::vec3<float_t> right() const {
        return forward().cross(camera_->up().value()).normalize();
    }
    xcmath::vec3<float_t> up() const {
        return right().cross(forward()).normalize();
    }

    void move(Direction direction, float_t distance) {
        if (!camera_ || distance == 0.0f) return;
        xcmath::vec3<float_t> shift{0.0f, 0.0f, 0.0f};
        switch (direction) {
            case Direction::FORWARD:
                shift = +forward() * distance;
                break;
            case Direction::BACKWARD:
                shift = -forward() * distance;
                break;
            case Direction::LEFT:
                shift = -right() * distance;
                break;
            case Direction::RIGHT:
                shift = +right() * distance;
                break;
            case Direction::UP:
                shift = +up() * distance;
                break;
            case Direction::DOWN:
                shift = -up() * distance;
                break;
            default:
                return;
                break;
        }
        camera_->set_position(camera_->position().value() + shift);
        camera_->set_target(camera_->target().value() + shift);
    }

    void rotate(float_t dyaw, float_t dpitch) {
        if (!camera_ || (dyaw == 0.0f && dpitch == 0.0f)) return;
        yaw_ += dyaw;
        pitch_ += dpitch;
        XCAL_DEBUG(FpsCameraControler, FpsCameraControler)
            << std::format("yaw: {}, pitch: {}", yaw_, pitch_);

        yaw_ = std::fmod(yaw_, 360.0f);
        if (yaw_ < 0.0f) yaw_ += 360.0f;
        pitch_ = std::clamp(pitch_, -89.0f, 89.0f);
        std::cerr << std::format("yaw: {}, pitch: {}", yaw_, pitch_)
                  << std::endl;
        auto yaw = xcmath::radians(yaw_);
        auto pitch = xcmath::radians(pitch_);
        xcmath::vec3<float_t> forward{
            (float_t)(std::cos(yaw) * std::cos(pitch)),
            (float_t)(std::sin(pitch)),
            (float_t)(std::sin(yaw) * std::cos(pitch)),
        };
        camera_->set_target(camera_->position().value() + forward);
    }
};

}  // namespace xcal::camera