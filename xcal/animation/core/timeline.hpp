#pragma once
#include <xcal/public.h>

#include <cstddef>
#include <xcal/animation/core/abs_animation.hpp>

namespace xcal::animation {
class Timeline {
   private:
    std::vector<AbsAnimation *> animations_{};
    std::vector<AbsAnimation *> ready_animations_{};
    float_t duration_;
    float_t frame_rate_;
    float_t current_time_{};
    size_t current_animation_index_{};

   public:
    explicit Timeline(float_t duration) : duration_(duration) {}

   public:
    void add(AbsAnimation *animation) { animations_.push_back(animation); }
    void start() {
        ready_animations_ = animations_;
        std::sort(ready_animations_.begin(), ready_animations_.end(),
                  [](AbsAnimation *a, AbsAnimation *b) {
                      return a->start_time() < b->start_time();
                  });
        current_animation_index_ = 0;
        current_time_ = 0.0f;
    }
    void update(float_t delta_time) {
        if (current_animation_index_ >= ready_animations_.size()) return;
        for (size_t i = current_animation_index_; i < ready_animations_.size();
             ++i) {
            auto animation = ready_animations_[i];
            if (animation->start_time() > current_time_) {
                current_animation_index_ = i;
                continue;
            }
        }
    }

   public:
    Timeline(const Timeline &) = default;
    Timeline(Timeline &&) = default;
    Timeline &operator=(const Timeline &) = default;
    Timeline &operator=(Timeline &&) = default;
};
}  // namespace xcal::animation