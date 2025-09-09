#pragma once
#include <xcal/public.h>

#include <xcal/animation/core/abs_animation.hpp>

namespace xcal::animation {

class XCAL_API Timeline {
   public:
   private:
    std::vector<AnimationHandle> animations_{};
    float_t duration_;

   public:
    explicit Timeline(float_t duration) : duration_(duration) {}

   public:
    void add(AbsAnimation *animation, float_t start_time, float_t duration) {
        animations_.emplace_back(
            AnimationHandle{animation, start_time, duration});
        if (start_time + duration > duration_) {
            duration_ = start_time + duration;
        }
    }

   public:
    Timeline(const Timeline &) = default;
    Timeline(Timeline &&) = default;
    Timeline &operator=(const Timeline &) = default;
    Timeline &operator=(Timeline &&) = default;
};
}  // namespace xcal::animation