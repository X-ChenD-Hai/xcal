#pragma once
#include <xcal/mobject/core/mobject.hpp>

namespace xcal::mobject {

class Rectangle : public MObject {
    XCAL_MOBJECT_TYPE(Rectangle)
   private:
    property::Position pos_;
    property::Scalar width_;
    property::Scalar height_;

   public:
    Rectangle(property::Position pos, property::Scalar width,
              property::Scalar height)
        : MObject(pos), width_(width), height_(height) {
        register_properties(pos_, width_, height_);
    }
    const property::Scalar& width() const { return width_; }
    property::Scalar& width() { return width_; }
    const property::Scalar& height() const { return height_; }
    property::Scalar& height() { return height_; }
    virtual ~Rectangle() override = default;
};

}  // namespace xcal::mobject
