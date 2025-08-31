#pragma once
#include <xcal/mobject/properties/time_point.hpp>

namespace xcal::scene {
class AbsFrame {
   private:
    mobject::property::TimePoint time_point_;

   public:
    AbsFrame(const mobject::property::TimePoint& time_point)
        : time_point_(time_point) {}
    const mobject::property::TimePoint& time_point() const {
        return time_point_;
    }
    virtual ~AbsFrame() = 0;
};
}  // namespace xcal::scene