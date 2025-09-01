#pragma once
#include <xcal/public.h>

#include <memory>
#include <xcal/mobject/core/abs_mobject.hpp>
#include <xcal/property/color.hpp>
#include <xcal/property/position.hpp>
#include <xcal/property/scalar.hpp>

namespace xcal::mobject {
class MObject : public AbsMObject {
   private:
    virtual Type type_() const = 0;

   private:
    property::Position pos_{0.0, 0.0};
    property::Color stroke_color_{0.0, 0.0, 0.0, 1.0};
    property::Color fill_color_{0.0, 0.0, 0.0, 1.0};
    property::Scalar stroke_width_{1.0};
    property::Scalar scale_x_{1.0};
    property::Scalar scale_y_{1.0};
    property::Scalar rotation_{0.0};
    property::Scalar depth_{1.0};

   public:
    MObject() : MObject({0, 0}) {};
    MObject(property::Position pos) : AbsMObject(), pos_(pos) {
        register_properties(pos_, stroke_color_, fill_color_, stroke_width_,
                            scale_x_, scale_y_, rotation_, depth_);
    }

    const property::Position& pos() const { return pos_; }
    property::Position& pos() { return pos_; }
    const property::Color& stroke_color() const { return stroke_color_; }
    property::Color& stroke_color() { return stroke_color_; }
    const property::Color& fill_color() const { return fill_color_; }
    property::Color& fill_color() { return fill_color_; }
    const property::Scalar& stroke_width() const { return stroke_width_; }
    property::Scalar& stroke_width() { return stroke_width_; }
    const property::Scalar& scale_x() const { return scale_x_; }
    property::Scalar& scale_x() { return scale_x_; }
    const property::Scalar& scale_y() const { return scale_y_; }
    property::Scalar& scale_y() { return scale_y_; }
    const property::Scalar& rotation() const { return rotation_; }
    property::Scalar& rotation() { return rotation_; }
    const property::Scalar& depth() const { return depth_; }
    property::Scalar& depth() { return depth_; }

    void rotate(float_t angle) { rotation_ += angle; }
    void scale(float_t x, float_t y) {
        scale_x_ *= x;
        scale_y_ *= y;
    }
    virtual ~MObject() = default;
};

using mobject_ptr = std::unique_ptr<mobject::MObject>;
}  // namespace xcal::mobject
