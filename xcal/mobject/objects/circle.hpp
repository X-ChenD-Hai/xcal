#pragma once
#include <xcal/mobject/core/mobject.hpp>

#include "xcal/mobject/core/composedmobject.hpp"
#include "xcal/property/vec.hpp"
#include "xcal/public.h"

namespace xcal::mobject {

/**
 * @brief 圆形图形对象类
 *
 * 表示一个圆形图形对象，继承自 MObject 基类。
 * 具有位置和半径属性，支持半径的获取和设置。
 */
class XCAL_API Circle
    : public ComposedMObject<Circle, BaseTransformableMobject,
                             StrokeableMObject, FillableMObject> {
    XCAL_MOBJECT_TYPE(Circle)

   private:
    property::Scalar radius_{1.0};  ///< 半径属性

   public:
    /**
     * @brief 构造函数
     * @param pos 圆心位置，默认为 (0.0, 0.0)
     * @param radius 半径值，默认为 1.0
     */
    Circle(const property::Vec<float_t, 3>& pos = {0.0, 0.0, 0.0},
           float_t radius = 1.0)
        : radius_(radius) {
        set_pos(pos);
        register_properties(radius_);
    }

    /**
     * @brief 获取半径值
     * @return float_t 半径值
     */
    float_t radius() const { return radius_.value(); }

    /**
     * @brief 设置半径值
     * @param radius 新的半径值
     */
    Circle* set_radius(float_t radius) {
        radius_ = radius;
        return this;
    }

    /**
     * @brief 析构函数
     */
    virtual ~Circle() override = default;
};

}  // namespace xcal::mobject
