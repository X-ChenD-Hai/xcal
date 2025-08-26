#pragma once
#include <public.h>

#include <memory>
#include <mobject/property.hpp>
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
class Polygone : public MObject {
    XCAL_MOBJECT_TYPE(Polygone)
   private:
    property::PositionList points_;

   public:
    Polygone() : MObject(), points_({}) { register_properties(points_); }
    template <typename... Args>
        requires std::constructible_from<property::PositionList, Args...>
    Polygone(Args&&... args)
        : MObject(),
          points_(std::make_unique<property::PositionList>(
              std::forward<Args>(args)...)) {
        register_properties(points_);
        points_.closed() = true;
    }
    const std::vector<property::Position>& points() const {
        return points_.positions();
    }
    void set_points(const property::PositionList& points) { points_ = points; }
    virtual ~Polygone() override = default;
};
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
class Line : public MObject {
    XCAL_MOBJECT_TYPE(Line)
   private:
    property::Position start_;
    property::Position end_;

   public:
    Line(property::Position start, property::Position end)
        : MObject(start), start_(start), end_(end) {
        register_properties(start_, end_);
    }
    const property::Position& start() const { return start_; }
    property::Position& start() { return start_; }
    const property::Position& end() const { return end_; }
    property::Position& end() { return end_; }
    virtual ~Line() override = default;
};
class Path : public MObject {
    XCAL_MOBJECT_TYPE(Path)
   private:
    property::PositionList points_;

   public:
    Path(property::PositionList points)
        : MObject(), points_(std::move(points)) {
        register_properties(points_);
    }
    const property::PositionList& points() const { return points_; }
    void set_points(const property::PositionList& points) { points_ = points; }
    virtual ~Path() override = default;
};
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
class Ellipse : public MObject {
    XCAL_MOBJECT_TYPE(Ellipse)
   private:
    property::Position pos_;
    property::Scalar radius_x_;
    property::Scalar radius_y_;

   public:
    Ellipse(property::Position pos, property::Scalar radius_x,
            property::Scalar radius_y)
        : MObject(pos), radius_x_(radius_x), radius_y_(radius_y) {
        register_properties(pos_, radius_x_, radius_y_);
    }
    const property::Scalar& radius_x() const { return radius_x_; }
    property::Scalar& radius_x() { return radius_x_; }
    const property::Scalar& radius_y() const { return radius_y_; }
    property::Scalar& radius_y() { return radius_y_; }
    virtual ~Ellipse() override = default;
};

using mobject_ptr = std::unique_ptr<mobject::MObject>;
}  // namespace xcal::mobject