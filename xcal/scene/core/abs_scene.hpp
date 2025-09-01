#pragma once
#include <xcal/public.h>

#include <vector>
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
class AbsScene {
   private:
    using object_t = ObjectPtr::element_type;  ///< 对象类型定义
    std::vector<ObjectPtr> mobjects_;          ///< 对象指针列表
    std::vector<std::unique_ptr<camera::AbsCamera>> cameras_;  ///< 相机列表

   public:
    /**
     * @brief 添加智能指针对象
     * @param obj 要添加的对象智能指针
     * @return typename ObjectPtr::element_type* 添加对象的原始指针
     */
    virtual typename ObjectPtr::element_type* add(ObjectPtr obj) {
        return mobjects_.emplace_back(std::move(obj)).get();
    }

    /**
     * @brief 添加裸指针对象（转换为智能指针）
     * @param obj 要添加的对象裸指针
     * @return typename ObjectPtr::element_type* 添加对象的原始指针
     */
    virtual typename ObjectPtr::element_type* add(
        typename ObjectPtr::element_type* obj) {
        return mobjects_.emplace_back(obj).get();
    }
    /**
     * @brief 添加对象（裸指针）
     * @tparam T 对象类型（必须继承自 object_t）
     * @param obj 要添加的对象（裸指针）
     * @return T* 添加对象的原始指针
     * @return T* 添加对象的原始指针
     */
    template <typename T>
        requires std::is_base_of_v<object_t, T>
    T* add(T* obj) {
        return (T*)mobjects_.emplace_back((object_t*)obj).get();
    }

    /**
     * @brief 添加对象（移动语义）
     * @tparam T 对象类型（必须继承自 object_t）
     * @param obj 要添加的对象（右值引用）
     * @return T* 添加对象的原始指针
     */
    template <typename T>
        requires std::is_base_of_v<object_t, T>
    T* add(T&& obj) {
        return (T*)mobjects_.emplace_back((object_t*)new T{std::move(obj)})
            .get();
    }

    /**
     * @brief 构造并添加对象
     * @tparam T 要构造的对象类型
     * @tparam Args 构造参数类型
     * @param args 构造参数
     * @return T* 构造并添加的对象的原始指针
     * @note 要求 T 可构造且继承自 ObjectPtr::element_type
     */
    template <class T, typename... Args>
        requires std::constructible_from<T, Args...> &&
                 std::is_base_of_v<typename ObjectPtr::element_type, T>
    T* add(Args&&... args) {
        auto ptr = std::make_unique<T>(std::forward<Args>(args)...);
        T* result = ptr.get();
        mobjects_.emplace_back(std::move(ptr));
        return result;
    }

    /**
     * @brief 获取对象列表（可修改）
     * @return std::vector<ObjectPtr>& 对象指针列表引用
     */
    std::vector<ObjectPtr>& mobjects() { return mobjects_; }

    /**
     * @brief 获取对象列表（只读）
     * @return const std::vector<ObjectPtr>& 对象指针列表常量引用
     */
    const std::vector<ObjectPtr>& mobjects() const { return mobjects_; }

   public:
    /**
     * @brief 虚析构函数
     */
    virtual ~AbsScene() = default;
};

}  // namespace xcal::scene
