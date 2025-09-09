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
    void ready_to_play() {
        animation_drivers_.clear();
        for (auto &animation : timeline_->animations()) {
            animation_drivers_.emplace_back(std::make_unique<AnimationDriver>(
                animation.get(), frame_rate_));
            duration_ = std::max(duration_,
                                 animation->start_time + animation->duration);
        }
    }
    void next() {
        for (auto &animation_driver : animation_drivers_) {
            if (animation_driver->start_time() <= current_time_) {
                animation_driver->next();
            }
        }
        animation_drivers_.erase(
            std::remove_if(animation_drivers_.begin(), animation_drivers_.end(),
                           [](const auto &ptr) { return ptr->finished(); }),
            animation_drivers_.end());
        current_time_ += 1.0f / frame_rate_;
    }
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