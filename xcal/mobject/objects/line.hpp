#pragma once

#include <xcal/public.h>

#include <xcal/mobject/core/composedmobject.hpp>
#include <xcal/mobject/core/mobject.hpp>
#include <xcal/property/vec.hpp>

namespace xcal::mobject {

class XCAL_API Line : public ComposedMObject<Line, BaseTransformableMobject,
                                             StrokeableMObject> {
    XCAL_MOBJECT_TYPE(Line)
   public:
    using vec = xcmath::vec<float_t, 3>;
    using vec4 = xcmath::vec<float_t, 4>;

   private:
    property::Vec<float_t, 3> direct_;

   public:
    Line(float_t x1, float_t y1, float_t z1, float_t x2, float_t y2, float_t z2)
        : Line({x1, y1, z1}, {x2, y2, z2}) {}
    Line(const vec& start, const vec& end)
        : ComposedMObject{}, direct_(end - start) {
        set_pos({(start.x() + end.x()) / 2, (start.y() + end.y()) / 2, 0});
    }
    Line(float_t length) : direct_(vec{length, 0.0f}) {}

    const vec4 start() const {
        return vec4{pos().value() - (direct_.value() / 2.f), 1.0f};
    }
    const vec4 end() const {
        return vec4{pos().value() + (direct_.value() / 2.f), 1.0f};
    }
    const vec& direct() const { return direct_.value(); }
    property::Vec<float_t, 3>& direct() { return direct_; }
    vec4 center() const { return vec4{pos().value(), 1.0f}; }

    virtual ~Line() override = default;
};

}  // namespace xcal::mobject
