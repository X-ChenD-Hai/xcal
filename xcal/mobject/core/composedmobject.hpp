/**
 * @file composedmobject.hpp
 * @author X_Chen D_Hai (illuminatestar@foxmail.com)
 * @brief
 * @version 0.1
 * @date 2025-09-18
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once
#include <xcal/public.h>

#include <xcal/mobject/core/abs_mobject.hpp>
#include <xcal/property/color.hpp>
#include <xcal/property/position.hpp>
#include <xcal/property/scalar.hpp>
#include <xcal/property/vec.hpp>
#include <xcmath/xcmath.hpp>

namespace xcal::mobject {
template <typename T>
class PositionableMObject {
   protected:
    property::Vec<float_t, 3> pos_{0.0, 0.0, 0.0};  ///< 对象位置属性
   public:
    T* set_pos(const property::Vec<float_t, 3>::data_t& pos) {
        pos_ = pos;
        return static_cast<T*>(this);
    }
    T* translate(float_t x, float_t y = 0, float_t z = 0) {
        pos_ = pos_.value() + property::Vec<float_t, 3>::data_t{x, y, z};
        return static_cast<T*>(this);
    }
    const property::Vec<float_t, 3>& pos() const { return pos_; }
};
template <typename T>
class ScalableMObject {
   protected:
    property::Vec<float_t, 3> scale_{1.0, 1.0, 1.0};  ///< 对象缩放属性
   public:
    T* set_scale(const property::Vec<float_t, 3>::data_t& scale) {
        scale_ = scale;
        return static_cast<T*>(this);
    }
    const property::Vec<float_t, 3>& scale() const { return scale_; }
    T* scale(float_t x, float_t y, float_t z) {
        scale_ = scale_.value() * property::Vec<float_t, 3>::data_t{x, y, z};
        return static_cast<T*>(this);
    }
    T* scale(float_t s) {
        scale_ = scale_.value() * s;
        return static_cast<T*>(this);
    }

    float_t scale_x() const { return scale_.value()[0]; }
    float_t scale_y() const { return scale_.value()[1]; }
    float_t scale_z() const { return scale_.value()[2]; }
};
template <typename T>
class RotatableMObject {
   protected:
    property::Vec<float_t, 3> rotation_{0.0, 0.0, 0.0};  ///< 对象旋转属性
   public:
    T* set_rotation(const property::Vec<float_t, 3>::data_t& rotation) {
        rotation_ = rotation;
        return static_cast<T*>(this);
    }
    const property::Vec<float_t, 3>& rotation() const { return rotation_; }
    T* rotate(float_t angle) {
        rotation_.value().z() += angle;
        return static_cast<T*>(this);
    }
};
template <typename T>
class StrokeableMObject {
   protected:
    property::Color stroke_color_{0.0, 0.0, 0.0, 1.0};  ///< 线条颜色属性
    property::Scalar stroke_width_{1.0};                ///< 线条宽度属性
   public:
    T* set_stroke_color(const property::Color::data_t& color) {
        stroke_color_ = color;
        return static_cast<T*>(this);
    }
    T* set_stroke_color(float_t r, float_t g, float_t b, float_t a = 1.0) {
        stroke_color_ = property::Color::data_t{r, g, b, a};
        return static_cast<T*>(this);
    }
    const property::Color& stroke_color() const { return stroke_color_; }
    T* set_stroke_width(property::Scalar::data_t width) {
        stroke_width_ = width;
        return static_cast<T*>(this);
    }
    const property::Scalar::data_t& stroke_width() const {
        return stroke_width_;
    }
};
template <typename T>
class FillableMObject {
   protected:
    property::Color fill_color_{0.0, 0.0, 0.0, 1.0};  ///< 填充颜色属性
   public:
    T* set_fill_color(const property::Color::data_t& color) {
        fill_color_ = color;
        return static_cast<T*>(this);
    }
    const property::Color& fill_color() const { return fill_color_; }
};
template <class T>
class BaseTransformableMobject : public PositionableMObject<T>,
                                 public ScalableMObject<T>,
                                 public RotatableMObject<T> {
   public:
    BaseTransformableMobject()
        : PositionableMObject<T>(),
          ScalableMObject<T>(),
          RotatableMObject<T>() {}
};

template <typename _Derived, template <class> typename... _PropertyMObjects>
class XCAL_API ComposedMObject : public AbsMObject,
                                 public _PropertyMObjects<_Derived>... {
   public:
    ComposedMObject() : _PropertyMObjects<_Derived>{}... {}
};

template <class T>
struct MObjectProperties {
    static constexpr auto is_mobject = std::derived_from<T, AbsMObject>;
    static constexpr auto is_scaleable =
        std::derived_from<T, ScalableMObject<T>>;
    static constexpr auto is_positionable =
        std::derived_from<T, PositionableMObject<T>>;
    static constexpr auto is_rotatable =
        std::derived_from<T, RotatableMObject<T>>;
    static constexpr auto is_strokeable =
        std::derived_from<T, StrokeableMObject<T>>;
    static constexpr auto is_fillable =
        std::derived_from<T, FillableMObject<T>>;
    static constexpr auto is_transformable =
        std::derived_from<T, BaseTransformableMobject<T>>;
};
#ifdef _HAS_CXX20
template <typename T>
concept is_mobject = std::derived_from<T, AbsMObject>;
template <typename T>
concept is_scaleable = std::derived_from<T, ScalableMObject<T>>;
template <typename T>
concept is_positionable = std::derived_from<T, PositionableMObject<T>>;
template <typename T>
concept is_rotatable = std::derived_from<T, RotatableMObject<T>>;
template <typename T>
concept is_strokeable = std::derived_from<T, StrokeableMObject<T>>;
template <typename T>
concept is_fillable = std::derived_from<T, FillableMObject<T>>;
template <typename T>
concept is_transformable = std::derived_from<T, BaseTransformableMobject<T>>;
#endif
}  // namespace xcal::mobject