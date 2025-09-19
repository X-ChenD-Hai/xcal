/**
 * @file mobject.hpp
 * @author X_Chen D_Hai (illuminatestar@foxmail.com)
 * @brief 基础图形对象类
 * @version 0.1
 * @date 2025-09-07
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once
#include <xcal/public.h>

#include <memory>
#include <xcal/mobject/core/abs_mobject.hpp>
#include <xcal/property/color.hpp>
#include <xcal/property/position.hpp>
#include <xcal/property/scalar.hpp>
#include <xcmath/xcmath.hpp>

#include "xcmath/mobject/function.hpp"
#include "xcmath/mobject/vec.hpp"

namespace xcal::mobject {

/**
 * @brief 基础图形对象类
 *
 * 继承自抽象图形对象基类，提供具体的图形对象属性和变换功能。
 * 包含位置、颜色、缩放、旋转等基本图形属性。
 */
// class XCAL_API MObject : public AbsMObject {
//    public:
//     using vec4 = xcmath::vec4<float_t>;  ///< 4维向量类型
//     using vec3 = xcmath::vec3<float_t>;  ///< 3维向量类型
//     using mat4 = xcmath::mat4<float_t>;  ///< 4x4矩阵类型
//     using mat3 = xcmath::mat3<float_t>;  ///< 3x3矩阵类型
//     using mat2 = xcmath::mat3<
//         float_t>;  ///< 2x2矩阵类型（注意：当前使用mat3，可能需要修正）

//    private:
//     virtual Type type_() const = 0;

//    private:
//     property::Position pos_{0.0, 0.0};                  ///< 对象位置属性
//     property::Color stroke_color_{0.0, 0.0, 0.0, 1.0};  ///< 描边颜色属性
//     property::Color fill_color_{0.0, 0.0, 0.0, 1.0};    ///< 填充颜色属性
//     property::Scalar stroke_width_{1.0};                ///< 描边宽度属性
//     property::Scalar scale_x_{1.0};                     ///< X轴缩放属性
//     property::Scalar scale_y_{1.0};                     ///< Y轴缩放属性
//     property::Scalar rotation_{0.0};                    ///< 旋转角度属性
//     property::Scalar depth_{0.0};                       ///< 深度属性

//    public:
//     /**
//      * @brief 默认构造函数
//      * @note 使用默认位置 {0, 0} 初始化
//      */
//     MObject() : MObject({0, 0}) {};

//     /**
//      * @brief 带位置参数的构造函数
//      * @param pos 初始位置
//      */
//     MObject(const property::Position::data_t& pos) : AbsMObject(), pos_(pos)
//     {
//         register_properties(pos_, stroke_color_, fill_color_, stroke_width_,
//                             scale_x_, scale_y_, rotation_, depth_);
//     }

//     const property::Position& pos() const { return pos_; }
//     property::Position& pos() { return pos_; }
//     const property::Color& stroke_color() const { return stroke_color_; }
//     property::Color& stroke_color() { return stroke_color_; }
//     const property::Color& fill_color() const { return fill_color_; }
//     property::Color& fill_color() { return fill_color_; }
//     const property::Scalar& stroke_width() const { return stroke_width_; }
//     property::Scalar& stroke_width() { return stroke_width_; }
//     const property::Scalar& scale_x() const { return scale_x_; }
//     property::Scalar& scale_x() { return scale_x_; }
//     const property::Scalar& scale_y() const { return scale_y_; }
//     property::Scalar& scale_y() { return scale_y_; }
//     const property::Scalar& rotation() const { return rotation_; }
//     property::Scalar& rotation() { return rotation_; }
//     const property::Scalar& depth() const { return depth_; }
//     property::Scalar& depth() { return depth_; }

//     MObject* set_pos(const property::Position::data_t& pos) {
//         pos_ = pos;
//         return this;
//     }
//     MObject* set_stroke_color(const property::Color::data_t& color) {
//         stroke_color_ = color;
//         return this;
//     }
//     MObject* set_fill_color(const property::Color::data_t& color) {
//         fill_color_ = color;
//         return this;
//     }
//     MObject* set_stroke_width(float_t width) {
//         stroke_width_ = width;
//         return this;
//     }
//     MObject* set_scale(float_t sx, float_t sy) {
//         scale_x_ = sx;
//         scale_y_ = sy;
//         return this;
//     }
//     MObject* set_rotation(float_t angle) {
//         rotation_ = angle;
//         return this;
//     }
//     MObject* set_depth(float_t depth) {
//         depth_ = depth;
//         return this;
//     }
//     MObject* translate(float_t x, float_t y) {
//         pos_.x() += x;
//         pos_.y() += y;
//         return this;
//     }
//     MObject* translate(const std::array<float_t, 2>& pos) {
//         pos_.x() += pos[0];
//         pos_.y() += pos[1];
//         return this;
//     }

//     MObject* rotate(float_t angle) {
//         rotation_ += angle;
//         return this;
//     }
//     MObject* scale(float_t x, float_t y) {
//         scale_x_ *= x;
//         scale_y_ *= y;
//         return this;
//     }

//     MObject* scale(const float_t& scale) {
//         scale_x_ *= scale;
//         scale_y_ *= scale;
//         return this;
//     }

//     vec4 local_to_global(const vec4& local) const {
//         if (rotation_ == 0.0 && scale_x_ == 1.0 && scale_y_ == 1.0)
//             return local + vec4(pos_.value().xy(), 0.0, 0.0);
//         else if (scale_x_ == 1.0 && scale_y_ == 1.0) {
//             return xcmath::translate(
//                        xcmath::rotate(mat4::eye(), rotation_.value(),
//                                       {0.0f, 0.0f, 1.0f}),
//                        vec3{pos_.value(), 0.0f}) ^
//                    local;
//         }
//         return xcmath::translate(
//                    xcmath::rotate(xcmath::scale(xcmath::mat4<float_t>::eye(),
//                                                 {scale_x_.value(),
//                                                  scale_y_.value(), 1.0f}),
//                                   rotation_.value(), {0.0f, 0.0f, 1.0f}),
//                    vec3{pos_.value(), 0.0f}) ^
//                local;
//     }
//     vec4 global_to_local(const vec4& global) const {
//         if (rotation_ == 0.0 && scale_x_ == 1.0 && scale_y_ == 1.0) {
//             return global - vec4(pos_.value().xy(), 0.0, 0.0);
//         }
//         // Apply inverse transformations in reverse order
//         if (scale_x_ == 1.0 && scale_y_ == 1.0) {
//             return xcmath::rotate(xcmath::translate(mat4::eye(),
//                                                     vec3{-pos_.value(),
//                                                     0.0f}),
//                                   -rotation_.value(), {0.0f, 0.0f, 1.0f}) ^
//                    global;
//         }
//         return xcmath::scale(
//                    xcmath::rotate(xcmath::translate(mat4::eye(),
//                                                     vec3{-pos_.value(),
//                                                     0.0f}),
//                                   -rotation_.value(), {0.0f, 0.0f, 1.0f}),
//                    {1.0f / scale_x_.value(), 1.0f / scale_y_.value(), 1.0f})
//                    ^
//                global;
//     }
//     virtual ~MObject() = default;
// };

// using mobject_ptr = std::unique_ptr<mobject::MObject>;
}  // namespace xcal::mobject
