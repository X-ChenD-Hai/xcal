/**
 * @file abs_camera.hpp
 * @author X_Chen D_Hai (illuminatestar@foxmail.com)
 * @brief 抽象相机基类
 * @version 0.1
 * @date 2025-09-07
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once
#include <xcal/public.h>

#include <xcal/camera/core/frame.hpp>
#include <xcal/property/color.hpp>
#include <xcal/property/vec.hpp>
#include <xcmath/xcmath.hpp>

namespace xcal::camera {
enum class CameraType {
    Perspective,  ///< 透视相机
    Orthogonal,   ///< 正交相机
};
#define XCAL_CAMERA_TYPE(tp)                                     \
   private:                                                      \
    ::xcal::camera::CameraType type_() const noexcept override { \
        return ::xcal::camera::CameraType::tp;                   \
    }

/**
 * @brief 相机系统命名空间
 *
 * 包含相机相关的类和功能，提供视图和投影矩阵管理。
 */

/**
 * @brief 抽象相机基类
 *
 * 提供相机基础功能，包括视图矩阵、投影矩阵计算和缓存管理。
 * 所有具体相机类（正交相机、透视相机）都应该继承自此类。
 */
class XCAL_API AbsCamera {
    using vec = xcmath::vec<float_t, 3>;

   private:
    virtual CameraType type_() const noexcept = 0;  ///< 相机类型
   private:
    /* 视图参数 */
    property::Vec<float_t, 3> position_{0.f, 0.f, -1.f};  ///< 相机位置向量
    property::Vec<float_t, 3> target_{0.f, 0.f, 0.f};     ///< 相机目标点向量
    property::Vec<float_t, 3> up_{0.f, 1.f, 0.f};
    property::Color background_color_{0.f, 0.f, 0.f, 1.f};  ///< 相机上方向向量
    mutable bool_t view_or_projection_has_changed_{
        true};  ///< 视图或投影矩阵是否已改变
    mutable xcmath::mat<float_t, 4, 4> view_matrix_cache_{
        xcmath::mat<float_t, 4, 4>::eye()};  ///< 视图矩阵缓存
    mutable xcmath::mat<float_t, 4, 4> pv_matrix_cache_{
        xcmath::mat<float_t, 4, 4>::eye()};  ///< 投影视图矩阵缓存

   private:
    /**
     * @brief 更新视图矩阵
     * @note 内部方法，根据相机位置、目标点和上方向重新计算视图矩阵
     */
    void update_view_matrix() const;

   public:
    /* 获取投影矩阵 P */
    /**
     * @brief 获取相机位置（可修改）
     * @return property::Vec<float_t, 3>& 相机位置向量引用
     */
    property::Vec<float_t, 3>& position() { return position_; }

    /**
     * @brief 获取相机位置（只读）
     * @return const property::Vec<float_t, 3>& 相机位置向量常量引用
     */
    const property::Vec<float_t, 3>& position() const { return position_; }

    /**
     * @brief 获取相机目标点（可修改）
     * @return property::Vec<float_t, 3>& 相机目标点向量引用
     */
    property::Vec<float_t, 3>& target() { return target_; }

    /**
     * @brief 获取相机目标点（只读）
     * @return const property::Vec<float_t, 3>& 相机目标点向量常量引用
     */
    const property::Vec<float_t, 3>& target() const { return target_; }

    /**
     * @brief 获取相机上方向（可修改）
     * @return property::Vec<float_t, 3>& 相机上方向向量引用
     */
    property::Vec<float_t, 3>& up() { return up_; }

    /**
     * @brief 获取相机上方向（只读）
     * @return const property::Vec<float_t, 3>& 相机上方向向量常量引用
     */
    const property::Vec<float_t, 3>& up() const { return up_; }

    /**
     * @brief 获取背景颜色（可修改）
     *
     * @return property::Color& 背景颜色引用
     */
    property::Color& background_color() { return background_color_; }

    /**
     * @brief 获取背景颜色（只读）
     *
     * @return const property::Color& 背景颜色常量引用
     */
    const property::Color& background_color() const {
        return background_color_;
    }

    CameraType type() const { return type_(); }
    /**
     * @brief 设置相机位置
     * @tparam Args 参数类型
     * @param args 位置坐标参数
     * @return AbsCamera* this指针，支持链式调用
     */
    template <typename... Args>
        requires(std::is_constructible_v<vec, Args...>)
    AbsCamera* set_position(Args&&... args) {
        position_ = vec{float_t(std::forward<Args>(args))...};
        return this;
    }

    /**
     * @brief 设置相机目标点
     * @tparam Args 参数类型
     * @param args 目标点坐标参数
     * @return AbsCamera* this指针，支持链式调用
     */
    template <typename... Args>
        requires(std::is_constructible_v<vec, Args...>)
    AbsCamera* set_target(Args&&... args) {
        target_ = vec{float_t(std::forward<Args>(args))...};
        return this;
    }

    /**
     * @brief 设置相机上方向
     * @tparam Args 参数类型
     * @param args 上方向坐标参数
     * @return AbsCamera* this指针，支持链式调用
     */
    template <typename... Args>
        requires(std::is_constructible_v<vec, Args...>)
    AbsCamera* set_up(Args&&... args) {
        up_ = vec{float_t(std::forward<Args>(args))...};
        return this;
    }
    /**
     * @brief 设置背景颜色
     * @tparam Args 参数类型
     * @param args 背景颜色参数
     * @return AbsCamera* this指针，支持链式调用
     */
    template <typename... Args>
        requires(std::is_constructible_v<property::Color::data_t, Args...>)
    AbsCamera* set_background_color(Args&&... args) {
        background_color_ =
            property::Color::data_t{(float_t)std::forward<Args>(args)...};
        return this;
    }

    /* 获取视图矩阵 V */
    /**
     * @brief 获取视图矩阵
     * @return const xcmath::mat<float_t, 4, 4>& 视图矩阵常量引用
     */
    const xcmath::mat<float_t, 4, 4>& view_matrix() const;

   protected:
    /**
     * @brief 标记投影矩阵已改变
     * @note 子类在投影参数改变时应调用此方法
     */
    void projection_has_changed() const;

   public:
    /**
     * @brief 默认构造函数
     */
    AbsCamera() {};

    /**
     * @brief 虚析构函数
     */
    virtual ~AbsCamera() = default;

    /**
     * @brief 获取投影矩阵
     * @return const xcmath::mat<float_t, 4, 4>& 投影矩阵常量引用
     * @note 纯虚函数，必须在子类中实现
     */
    virtual const xcmath::mat<float_t, 4, 4>& projection_matrix() const = 0;

    /**
     * @brief 检查投影矩阵是否需要更新
     * @return bool_t true表示需要更新，false表示不需要
     * @note 纯虚函数，必须在子类中实现
     */
    virtual bool_t projection_should_update() const = 0;

    /**
     * @brief 检查视图矩阵是否需要更新
     * @return bool_t true表示需要更新，false表示不需要
     */
    bool_t view_should_update() const;

    /**
     * @brief 检查相机矩阵是否需要更新
     * @return bool_t true表示需要更新，false表示不需要
     */
    bool_t should_update() const;

    /**
     * @brief 获取投影视图矩阵（PV矩阵）
     * @return const xcmath::mat<float_t, 4, 4>& 投影视图矩阵常量引用
     */
    const xcmath::mat<float_t, 4, 4>& pv_matrix() const;
};
}  // namespace xcal::camera
template class XCAL_API xcal::property::Vec<float_t, 3>;
namespace xcal {
XCAL_API inline const char* to_string(xcal::camera::CameraType type) {
    switch (type) {
        case xcal::camera::CameraType::Perspective:
            return "Perspective";
        case xcal::camera::CameraType::Orthogonal:
            return "Orthogonal";
        default:
            return "Unknown";
    }
}
}  // namespace xcal