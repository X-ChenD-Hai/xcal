#pragma once
#include <public.h>

#include <memory>
#include <mobject/properties/scalar.hpp>
#include <mobject/properties/position.hpp>
#include <mobject/properties/color.hpp>
#define XCAL_MOBJECT_TYPE(type) \
    virtual Type type_() const override { return Type::type; }

namespace xcal::mobject {
enum class Type {
    Polygone,
    Circle,
    Line,
    Path,
    Rectangle,
    Ellipse,
};
class MObject {
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
    bool_t visible_ = {true};
    std::vector<property::MProperty*> properties_{};

   protected:
    template <class... Arg>
        requires(std::is_base_of_v<property::MProperty, Arg> && ...)
    void register_properties(Arg&... arg) {
        (properties_.push_back(static_cast<property::MProperty*>(&arg)), ...);
    }

   public:
    MObject() : MObject({0, 0}) {};
    MObject(property::Position pos) : pos_(pos) {
        register_properties(pos_, stroke_color_, fill_color_, stroke_width_,
                            scale_x_, scale_y_, rotation_, depth_);
    }

    const property::Position pos() const { return pos_; }
    property::Position& pos() { return pos_; }
    bool visible() const { return visible_; }
    bool& visible() { return visible_; }
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

    std::vector<property::MProperty*>& properties() { return properties_; }
    Type type() const { return type_(); };
    virtual ~MObject() = default;
};

using mobject_ptr = std::unique_ptr<mobject::MObject>;
}  // namespace xcal::mobject
