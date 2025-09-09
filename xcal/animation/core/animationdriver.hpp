/**
 * @file animationdriver.hpp
 * @author X_Chen D_Hai (illuminatestar@foxmail.com)
 * @brief This file contains the declaration of AnimationDriver class.
 * @version 0.1
 * @date 2025-09-09
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once
#include <xcal/public.h>

#include <cstddef>
#include <xcal/animation/core/abs_animation.hpp>

namespace xcal::animation {
class XCAL_API AnimationDriver {
   private:
    const AnimationHandle* handle_;
    const float_t frame_rate_;
    size_t current_frame_index_{0};

   public:
    AnimationDriver(AnimationHandle* handle, float_t frame_rate)
        : handle_(handle), frame_rate_(frame_rate) {}

   public:
    ~AnimationDriver() = default;

   public:
    bool finished() const { return current_frame_index_ >= frame_count(); }
    bool playing() const { return !finished() && current_frame_index_; }
    void next() {
        if (finished()) return;
        auto c = frame_count();
        handle_->animation->update_to((float_t)(current_frame_index_++) /
                                      (frame_count() - 1));
    }
    size_t frame_count() const { return handle_->duration * frame_rate_; }
    AbsAnimation* animation() const { return handle_->animation; }
    float_t start_time() const { return handle_->start_time; }
    float_t end_time() const { return handle_->start_time + handle_->duration; }
    float_t duration() const { return handle_->duration; }
    float_t frame_rate() const { return frame_rate_; }
    size_t current_frame_index() const { return current_frame_index_; }

   public:
    AnimationDriver(const AnimationDriver&) = delete;
    AnimationDriver(AnimationDriver&&) = delete;
    AnimationDriver& operator=(const AnimationDriver&) = delete;
    AnimationDriver& operator=(AnimationDriver&&) = delete;
};

}  // namespace xcal::animation