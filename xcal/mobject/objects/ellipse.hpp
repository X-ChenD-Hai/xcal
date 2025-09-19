#pragma once
#include <xcal/public.h>

#include <xcal/mobject/core/composedmobject.hpp>
#include <xcal/mobject/core/mobject.hpp>

#include "xcal/property/vec.hpp"

namespace xcal::mobject {

class XCAL_API Ellipse : public ComposedMObject<Line, BaseTransformableMobject,
                                                StrokeableMObject> {
    XCAL_MOBJECT_TYPE(Ellipse)
   private:
    property::Position pos_;
    property::Scalar radius_x_;
    property::Scalar radius_y_;

   public:
    Ellipse(const property::Vec<float_t, 3>::data_t& pos, float_t radius_x,
            float_t radius_y)
        : radius_x_(radius_x), radius_y_(radius_y) {
        set_pos(pos);
        register_properties(pos_, radius_x_, radius_y_);
    }
    const property::Scalar& radius_x() const { return radius_x_; }
    property::Scalar& radius_x() { return radius_x_; }
    const property::Scalar& radius_y() const { return radius_y_; }
    property::Scalar& radius_y() { return radius_y_; }
    virtual ~Ellipse() override = default;
};

}  // namespace xcal::mobject
