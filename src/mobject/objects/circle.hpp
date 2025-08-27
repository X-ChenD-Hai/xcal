#pragma once
#include <mobject/core/mobject.hpp>

namespace xcal::mobject {

/**
 * @brief 圆形图形对象类
 *
 * 表示一个圆形图形对象，继承自 MObject 基类。
 * 具有位置和半径属性，支持半径的获取和设置。
 */
class Circle : public MObject {
    XCAL_MOBJECT_TYPE(Circle)

   private:
    property::Scalar radius_{1.0};  ///< 半径属性

   public:
    /**
     * @brief 构造函数
     * @param pos 圆心位置，默认为 (0.0, 0.0)
     * @param radius 半径值，默认为 1.0
     */
    Circle(property::Position pos = {0.0, 0.0}, float_t radius = 1.0)
        : MObject(pos), radius_(radius) {
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
    void set_radius(float_t radius) { radius_ = radius; }

    /**
     * @brief 析构函数
     */
    virtual ~Circle() override = default;
};

}  // namespace xcal::mobject
