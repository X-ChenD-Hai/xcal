#pragma once
#include <mobject/core/mobject.hpp>

namespace xcal::mobject {

class Circle : public MObject {
    XCAL_MOBJECT_TYPE(Circle)

   private:
    property::Scalar radius_{1.0};

   public:
    Circle(property::Position pos = {0.0, 0.0}, float_t radius = 1.0)
        : MObject(pos), radius_(radius) {
        register_properties(radius_);
    }
    float_t radius() const { return radius_.value(); }
    void set_radius(float_t radius) { radius_ = radius; }
    virtual ~Circle() override = default;
};

}  // namespace xcal::mobject
