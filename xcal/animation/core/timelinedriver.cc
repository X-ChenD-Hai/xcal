#include <xcal/animation/core/timelinedriver.hpp>
void xcal::animation::TimelineDriver::ready_to_play() {
    animation_drivers_.clear();
    for (auto &animation : timeline_->animations()) {
        animation_drivers_.emplace_back(
            std::make_unique<AnimationDriver>(animation.get(), frame_rate_));
        duration_ =
            std::max(duration_, animation->start_time + animation->duration);
    }
}
void xcal::animation::TimelineDriver::next() {
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
