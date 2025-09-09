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
    AnimationHandle* handle_;
    float_t frame_rate_;
    size_t current_frame_index_{0};

   public:
    AnimationDriver(AnimationHandle* handle, float_t frame_rate)
        : handle_(handle), frame_rate_(frame_rate) {}

   public:
    ~AnimationDriver() = default;

   public:
    bool finished() const {
        return current_frame_index_ >= (handle_->duration / frame_rate_);
    }
    bool playing() const { return !finished() && current_frame_index_; }
    void update(float_t time) {
        if (time < handle_->start_time || finished()) return;
        ;
    }

   public:
    AnimationDriver(const AnimationDriver&) = delete;
    AnimationDriver(AnimationDriver&&) = delete;
    AnimationDriver& operator=(const AnimationDriver&) = delete;
    AnimationDriver& operator=(AnimationDriver&&) = delete;
};

}  // namespace xcal::animation