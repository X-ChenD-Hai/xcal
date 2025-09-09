/**
 * @file timelinedriver.hpp
 * @author X_Chen D_Hai (illuminatestar@foxmail.com)
 * @brief
 * @version 0.1
 * @date 2025-09-09
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once
#include <xcal/public.h>

#include <memory>
#include <vector>
#include <xcal/animation/core/animationdriver.hpp>
#include <xcal/animation/core/timeline.hpp>

namespace xcal::animation {

class XCAL_API TimelineDriver {
   private:
    Timeline *timeline_;
    std::vector<std::unique_ptr<AnimationDriver>> animation_drivers_;
    float_t frame_rate_ = 60.0f;
    float_t current_time_ = 0.0f;
    float_t duration_ = 0.0f;

   public:
    TimelineDriver(Timeline *timeline)
        : timeline_(timeline), animation_drivers_() {}
    ~TimelineDriver() = default;

   public:
    void ready_to_play();
    void next();
    bool finished() const {
        return duration_ <= current_time_ || animation_drivers_.empty();
    }

    float_t frame_rate() const { return frame_rate_; }
    TimelineDriver *set_frame_rate(float_t frame_rate) {
        frame_rate_ = frame_rate;
        return this;
    }
    float_t duration() const { return duration_; }

   public:
    TimelineDriver(const TimelineDriver &) = delete;
    TimelineDriver(TimelineDriver &&) = delete;
    TimelineDriver &operator=(const TimelineDriver &) = delete;
    TimelineDriver &operator=(TimelineDriver &&) = delete;
};

}  // namespace xcal::animation