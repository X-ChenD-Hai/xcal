#pragma once

#include <xcal/mobject/core/mobject.hpp>

#include "xcal/property/vec.hpp"
#include "xcal/public.h"

namespace xcal::mobject {

class Line : public MObject {
    XCAL_MOBJECT_TYPE(Line)
   public:
    using vec = xcmath::vec<float_t, 2>;

   private:
    property::Vec<float_t, 2> direct_;

   public:
    Line(float_t x1, float_t y1, float_t x2, float_t y2)
        : Line({x1, y1}, {x2, y2}) {}
    Line(const vec& start, const vec& end)
        : MObject({(start.x() + end.x()) / 2, (start.y() + end.y()) / 2}),
          direct_(end - start) {}
    Line(float_t length) : MObject(), direct_({length, 0.0f}) {}

    const vec4 start() const {
        return vec4{pos().data() - (direct_.value() / 2.f), 0.0f, 1.0f};
    }
    const vec4 end() const {
        return vec4{pos().data() + (direct_.value() / 2.f), 0.0f, 1.0f};
    }
    const vec& direct() const { return direct_.value(); }
    property::Vec<float_t, 2>& direct() { return direct_; }
    vec4 center() const { return MObject::vec4{pos().data(), 0.0f, 1.0f}; }

    virtual ~Line() override = default;
};

}  // namespace xcal::mobject
