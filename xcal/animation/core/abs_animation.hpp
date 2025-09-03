#pragma once
#include <xcal/public.h>

namespace xcal::animation {
constexpr float_t kEpsilon = 0.0001f;
class XCAL_API AbsAnimation {
   private:
    bool_t is_running_{false};
    float_t start_time_{0.0f};
    float_t duration_{0.0f};
    float_t elapsed_time_{0.0f};

   public:
    AbsAnimation() = default;
    virtual ~AbsAnimation() = default;

   public:
    const float_t& duration() const { return duration_; }

    AbsAnimation* set_duration(float_t duration) {
        duration_ = duration;
        return this;
    }

    const float_t& start_time() const { return start_time_; }

    AbsAnimation* set_start_time(float_t start_time) {
        start_time_ = start_time;
        return this;
    }

    bool_t is_running() const { return is_running_; }

    bool_t is_paused() const { return !is_running_ && elapsed_time_ > 0.0f; }

    bool_t is_finished() const {
        return is_running_ && elapsed_time_ >= duration_;
    }

    float_t elapsed_time() const { return elapsed_time_; }

    void set_elapsed_time(float_t elapsed_time) {
        elapsed_time_ = elapsed_time;
        if (elapsed_time_ < 0.0f) {
            update_to(0.0f);
        } else if (elapsed_time_ > duration_) {
            update_to(duration_);
        }
    }

   public:
    virtual void update(float_t dt = kEpsilon) = 0;
    virtual void update_to(float_t time) {};
    virtual void start() = 0;
    virtual void pause() = 0;
    virtual void resume() = 0;
    virtual void stop() = 0;
};
}  // namespace xcal::animation