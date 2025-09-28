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
    enum class Direction {
        FORWARD,
        BACKWARD,
        LEFT,
        RIGHT,
        UP,
        DOWN,
    };

   private:
    AbsCamera* camera_;

    float_t yaw_;
    float_t pitch_;

   public:
    FpsCameraControler(AbsCamera* camera) : camera_(camera) {}

   public:
    void set_camera(AbsCamera* camera) {
        camera_ = camera;
        yaw_ = 0.0f;
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
        switch (direction) {
            case Direction::FORWARD:
                camera_->position() =
                    camera_->position().value() + forward() * distance;
                break;
            case Direction::BACKWARD:
                camera_->position() =
                    camera_->position().value() - forward() * distance;
                break;
            case Direction::LEFT:
                camera_->position() =
                    camera_->position().value() - right() * distance;
                break;
            case Direction::RIGHT:
                camera_->position() =
                    camera_->position().value() + right() * distance;
                break;
            case Direction::UP:
                camera_->position() =
                    camera_->position().value() + up() * distance;
                break;
            case Direction::DOWN:
                camera_->position() =
                    camera_->position().value() - up() * distance;
                break;
            default:
                break;
        }
    }

    void rotate(float_t dyaw, float_t dpitch) {
        if (!camera_ || (dyaw == 0.0f && dpitch == 0.0f)) return;
        yaw_ += dyaw;
        pitch_ += dpitch;
        yaw_ = std::fmod(yaw_, 360.0f);
        if (yaw_ < 0.0f) yaw_ += 360.0f;
        pitch_ = std::clamp(pitch_, -89.0f, 89.0f);
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