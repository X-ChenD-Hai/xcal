/**
 * @file abs_scene.hpp
 * @author X_Chen D_Hai (illuminatestar@foxmail.com)
 * @brief 抽象场景模板类
 * @version 0.1
 * @date 2025-09-07
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once
#include <xcal/public.h>

#include <memory>
#include <type_traits>
#include <vector>
#include <xcal/animation/core/abs_animation.hpp>
#include <xcal/animation/core/timeline.hpp>
#include <xcal/camera/core/abs_camera.hpp>
#include <xcal/mobject/core/abs_mobject.hpp>

namespace xcal::scene {

/**
 * @brief 抽象场景模板类
 *
 * 场景管理的抽象基类，使用模板支持不同类型的对象指针。
 * 提供对象添加、管理和访问功能。
 *
 * @tparam ObjectPtr 对象指针类型，默认为 mobject::AbsMObject_ptr
 */
template <typename ObjectPtr = mobject::AbsMObject_ptr>
class XCAL_API AbsScene {
   private:
    using object_t = ObjectPtr::element_type;  ///< 对象类型定义
    std::vector<ObjectPtr> mobjects_{};        ///< 对象指针列表
    std::vector<std::unique_ptr<camera::AbsCamera>> cameras_{};  ///< 相机列表
    std::vector<std::unique_ptr<animation::AbsAnimation>>
        animations_{};  ///< 动画列表
    std::vector<std::unique_ptr<animation::Timeline>>
        timelines_{};  ///< 时间线列表

   public:
    AbsScene() {};
    AbsScene(const AbsScene&) = delete;
    AbsScene& operator=(const AbsScene&) = delete;

    /**
     * @brief 添加对象/相机/动画/时间线
     *
     * @tparam T 要添加的对象类型
     * @param obj
     * @return T*
     */
    template <typename T = animation::Timeline, class... Args>
        requires std::constructible_from<T, Args...>
    T* add(Args&&... args) {
        if constexpr (std::is_base_of_v<animation::Timeline, T>)
            return (T*)timelines_.emplace_back(std::make_unique<T>(args...))
                .get();
        else if constexpr (std::is_base_of_v<animation::AbsAnimation, T>)
            return (T*)animations_.emplace_back(std::make_unique<T>(args...))
                .get();
        else if constexpr (std::is_base_of_v<mobject::AbsMObject, T>)
            return (T*)mobjects_.emplace_back(std::make_unique<T>(args...))
                .get();
        else if constexpr (std::is_base_of_v<camera::AbsCamera, T>)
            return (T*)cameras_.emplace_back(std::make_unique<T>(args...))
                .get();
        else
            static_assert(false, "unsupported type");
    }
    /**
     * @brief 添加对象/相机/动画/时间线
     *
     * @tparam T 要添加的对象类型
     * @param obj
     * @return T*
     */
    template <typename T>
    T* add(std::unique_ptr<T>&& obj) {
        if constexpr (std::is_base_of_v<object_t, T>)
            return (T*)mobjects_.emplace_back(std::move(obj)).get();
        else if constexpr (std::is_base_of_v<camera::AbsCamera, T>)
            return (T*)cameras_.emplace_back(std::move(obj)).get();
        else if constexpr (std::is_base_of_v<animation::AbsAnimation, T>)
            return (T*)animations_.emplace_back(std::move(obj)).get();
        else if constexpr (std::is_base_of_v<animation::Timeline, T>)
            return (T*)timelines_.emplace_back(std::move(obj)).get();
        else
            static_assert(false, "unsupported type");
    }
    /**
     * @brief 添加对象/相机/动画/时间线
     *
     * @tparam T
     * @param obj
     * @return T*
     */
    template <typename T>
    T* add(T* obj) {
        if constexpr (std::is_base_of_v<object_t, T>)
            return (T*)mobjects_.emplace_back(obj).get();
        else if constexpr (std::is_base_of_v<camera::AbsCamera, T>)
            return (T*)cameras_.emplace_back(obj).get();
        else if constexpr (std::is_base_of_v<animation::AbsAnimation, T>)
            return (T*)animations_.emplace_back(obj).get();
        else if constexpr (std::is_base_of_v<animation::Timeline, T>)
            return (T*)timelines_.emplace_back(obj).get();
        else
            static_assert(false, "unsupported type");
    }
    /**
     * @brief 添加对象/相机/动画/时间线
     *
     * @tparam T 要添加的对象类型
     * @param obj
     * @return T*
     */
    template <typename T>
    T* add(T&& obj) {
        if constexpr (std::is_base_of_v<object_t, T>)
            return (T*)mobjects_.emplace_back(std::move(obj)).get();
        else if constexpr (std::is_base_of_v<camera::AbsCamera, T>)
            return (T*)cameras_.emplace_back(std::move(obj)).get();
        else if constexpr (std::is_base_of_v<animation::AbsAnimation, T>)
            return (T*)animations_.emplace_back(std::move(obj)).get();
        else if constexpr (std::is_base_of_v<animation::Timeline, T>)
            return (T*)timelines_.emplace_back(std::move(obj)).get();
        else
            static_assert(false, "unsupported type");
    }

    /**
     * @brief 获取对象列表（可修改）
     * @return std::vector<ObjectPtr>& 对象指针列表引用
     */
    std::vector<ObjectPtr>& mobjects() { return mobjects_; }
    std::vector<std::unique_ptr<camera::AbsCamera>>& cameras() {
        return cameras_;
    }
    std::vector<std::unique_ptr<animation::Timeline>>& timelines() {
        return timelines_;
    }
    std::vector<std::unique_ptr<animation::AbsAnimation>>& animations() {
        return animations_;
    }

    /**
     * @brief 获取对象列表（只读）
     * @return const std::vector<ObjectPtr>& 对象指针列表常量引用
     */
    const std::vector<ObjectPtr>& mobjects() const { return mobjects_; }
    const std::vector<std::unique_ptr<camera::AbsCamera>>& cameras() const {
        return cameras_;
    }
    const std::vector<std::unique_ptr<animation::AbsAnimation>>& animations()
        const {
        return animations_;
    }

   public:
    /**
     * @brief 虚析构函数
     */
    virtual ~AbsScene() = default;
};

}  // namespace xcal::scene
