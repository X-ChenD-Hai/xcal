/**
 * @file perspectivecamera.hpp
 * @author X_Chen D_Hai (illuminatestar@foxmail.com)
 * @brief 透视相机类
 * @version 0.1
 * @date 2025-09-07
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once

#include <xcal/public.h>

#include <xcal/camera/core/abs_camera.hpp>
#include <xcal/property/scalar.hpp>
#include <xcal/property/vec.hpp>
#include <xcmath/xcmath.hpp>

namespace xcal::camera {

/**
 * @brief 透视相机类
 *
 * 实现透视投影相机功能，继承自抽象相机基类。
 * 透视相机模拟人眼视角，近大远小效果。
 */
class XCAL_API PerspectiveCamera : public AbsCamera {
   private:
    /* 投影参数 */
    property::Scalar fov_;     ///< 视野角度（Field of View）
    property::Scalar aspect_;  ///< 宽高比
    property::Scalar near_;    ///< 近裁剪平面距离
    property::Scalar far_;     ///< 远裁剪平面距离

    /* 缓存 */
    mutable xcmath::mat<float_t, 4, 4>
        projection_matrix_cache_{};  ///< 投影矩阵缓存

   public:
    /**
     * @brief 构造函数
     * @param fov 视野角度（弧度）
     * @param aspect 宽高比
     * @param near 近裁剪平面距离
     * @param far 远裁剪平面距离
     */
    PerspectiveCamera(float fov, float aspect, float near, float far)
        : AbsCamera(), fov_(fov), aspect_(aspect), near_(near), far_(far) {}

   public:
    /* 公共访问器方法 */
    /**
     * @brief 获取视野角度（可修改）
     * @return property::Scalar& 视野角度引用
     */
    property::Scalar& fov() { return fov_; }

    /**
     * @brief 获取视野角度（只读）
     * @return const property::Scalar& 视野角度常量引用
     */
    const property::Scalar& fov() const { return fov_; }

    /**
     * @brief 获取宽高比（可修改）
     * @return property::Scalar& 宽高比引用
     */
    property::Scalar& aspect() { return aspect_; }

    /**
     * @brief 获取宽高比（只读）
     * @return const property::Scalar& 宽高比常量引用
     */
    const property::Scalar& aspect() const { return aspect_; }

    /**
     * @brief 获取近裁剪平面距离（可修改）
     * @return property::Scalar& 近裁剪平面距离引用
     */
    property::Scalar& near() { return near_; }

    /**
     * @brief 获取近裁剪平面距离（只读）
     * @return const property::Scalar& 近裁剪平面距离常量引用
     */
    const property::Scalar& near() const { return near_; }

    /**
     * @brief 获取远裁剪平面距离（可修改）
     * @return property::Scalar& 远裁剪平面距离引用
     */
    property::Scalar& far() { return far_; }

    /**
     * @brief 获取远裁剪平面距离（只读）
     * @return const property::Scalar& 远裁剪平面距离常量引用
     */
    const property::Scalar& far() const { return far_; }

    /**
     * @brief 获取投影矩阵
     * @return const xcmath::mat<float_t, 4, 4>& 投影矩阵常量引用
     * @note 重写基类纯虚函数
     */
    const xcmath::mat<float_t, 4, 4>& projection_matrix() const override;

    /**
     * @brief 检查投影矩阵是否需要更新
     * @return bool_t true表示需要更新，false表示不需要
     * @note 重写基类纯虚函数
     */
    bool_t projection_should_update() const override;

   private:
    /**
     * @brief 更新投影矩阵
     * @note 内部方法，根据投影参数重新计算投影矩阵
     */
    void update_projection_matrix() const;
};

}  // namespace xcal::camera
