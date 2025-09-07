#pragma once
#include <xcal/mobject/core/mobject.hpp>

#include "xcal/public.h"

namespace xcal::mobject {

class XCAL_API Ellipse : public MObject {
    XCAL_MOBJECT_TYPE(Ellipse)
   private:
    property::Position pos_;
    property::Scalar radius_x_;
    property::Scalar radius_y_;

   public:
    Ellipse(const property::Position::data_t& pos, float_t radius_x,
            float_t radius_y)
        : MObject(pos), radius_x_(radius_x), radius_y_(radius_y) {
        register_properties(pos_, radius_x_, radius_y_);
    }
    const property::Scalar& radius_x() const { return radius_x_; }
    property::Scalar& radius_x() { return radius_x_; }
    const property::Scalar& radius_y() const { return radius_y_; }
    property::Scalar& radius_y() { return radius_y_; }
    virtual ~Ellipse() override = default;
};

}  // namespace xcal::mobject
