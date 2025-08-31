#pragma once
#include <public.h>

#include <mobject/core/mobject_types.hpp>
#include <property/core/property.hpp>

namespace xcal::mobject {

/**
 * @brief 抽象图形对象基类
 *
 * 所有图形对象的抽象基类，定义了图形对象的基本接口和属性管理功能。
 * 提供可见性控制和属性注册机制。
 */
class AbsMObject {
   private:
    /**
     * @brief 获取对象类型（纯虚函数）
     * @return Type 对象类型枚举值
     */
    virtual Type type_() const = 0;

   private:
    bool_t visible_ = {true};                         ///< 对象可见性标志
    std::vector<property::MProperty*> properties_{};  ///< 属性指针列表

   protected:
    /**
     * @brief 注册属性到对象
     * @tparam Arg 属性类型（必须继承自 MProperty）
     * @param arg 属性引用（可变参数）
     * @note 使用概念约束确保所有参数都是 MProperty 的派生类
     */
    template <class... Arg>
        requires(std::is_base_of_v<property::MProperty, Arg> && ...)
    void register_properties(Arg&... arg) {
        (properties_.push_back(static_cast<property::MProperty*>(&arg)), ...);
    }

   public:
    /**
     * @brief 默认构造函数
     */
    AbsMObject() = default;

   public:
    /**
     * @brief 获取对象可见性状态（只读）
     * @return bool 可见性状态
     */
    bool visible() const { return visible_; }

    /**
     * @brief 获取对象可见性状态（可修改）
     * @return bool& 可见性状态引用
     */
    bool& visible() { return visible_; }

    Type type() const { return type_(); }

    /**
     * @brief 获取对象属性列表
     * @return std::vector<property::MProperty*>& 属性指针列表引用
     */
    std::vector<property::MProperty*>& properties() { return properties_; }

    /**
     * @brief 虚析构函数
     */
    virtual ~AbsMObject() = default;
};

/**
 * @brief 抽象图形对象智能指针类型定义
 */
using AbsMObject_ptr = std::unique_ptr<AbsMObject>;

}  // namespace xcal::mobject
