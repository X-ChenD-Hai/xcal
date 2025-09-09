#pragma once
#include <xcal/public.h>

#include <memory>
#include <xcal/animation/core/abs_animation.hpp>

namespace xcal::animation {

class XCAL_API Timeline {
   public:
   private:
    std::vector<std::unique_ptr<AnimationHandle>> animations_{};

   public:
    explicit Timeline() {}

   public:
    void add(AbsAnimation *animation, float_t start_time, float_t duration) {
        animations_.emplace_back(
            std::make_unique<AnimationHandle>(animation, start_time, duration));
    }
    std::vector<std::unique_ptr<AnimationHandle>> &animations() {
        return animations_;
    }

   public:
    Timeline(const Timeline &) = delete;
    Timeline(Timeline &&) = default;
    Timeline &operator=(const Timeline &) = delete;
    Timeline &operator=(Timeline &&) = default;
};
}  // namespace xcal::animation