/**
 * @file abs_animation.hpp
 * @author X_Chen D_Hai (illuminatestar@foxmail.com)
 * @brief 抽象动画基类
 * @version 0.1
 * @date 2025-09-07
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once
#include <xcal/public.h>

namespace xcal::animation {

/**
 * @brief 动画系统命名空间
 *
 * 包含动画相关的类和功能，提供动画播放控制和时间管理。
 */
constexpr float_t kEpsilon = 0.0001f;  ///< 动画更新最小时间间隔

/**
 * @brief 抽象动画基类
 *
 * 提供动画基础功能，包括播放控制、时间管理和状态跟踪。
 * 所有具体动画类都应该继承自此类。
 */
class XCAL_API AbsAnimation {
   private:
    bool_t is_running_{false};    ///< 动画是否正在运行
    float_t start_time_{0.0f};    ///< 动画开始时间
    float_t duration_{0.0f};      ///< 动画总时长
    float_t elapsed_time_{0.0f};  ///< 已过去的时间

   public:
    /**
     * @brief 默认构造函数
     */
    AbsAnimation() = default;

    /**
     * @brief 虚析构函数
     */
    virtual ~AbsAnimation() = default;

   public:
    /**
     * @brief 获取动画时长
     * @return const float_t& 动画时长引用
     */
    const float_t& duration() const { return duration_; }

    /**
     * @brief 设置动画时长
     * @param duration 动画时长
     * @return AbsAnimation* this指针，支持链式调用
     */
    AbsAnimation* set_duration(float_t duration) {
        duration_ = duration;
        return this;
    }

    /**
     * @brief 获取动画开始时间
     * @return const float_t& 动画开始时间引用
     */
    const float_t& start_time() const { return start_time_; }

    /**
     * @brief 设置动画开始时间
     * @param start_time 动画开始时间
     * @return AbsAnimation* this指针，支持链式调用
     */
    AbsAnimation* set_start_time(float_t start_time) {
        start_time_ = start_time;
        return this;
    }

    /**
     * @brief 检查动画是否正在运行
     * @return bool_t true表示正在运行，false表示停止
     */
    bool_t is_running() const { return is_running_; }

    /**
     * @brief 检查动画是否暂停
     * @return bool_t true表示暂停，false表示未暂停
     */
    bool_t is_paused() const { return !is_running_ && elapsed_time_ > 0.0f; }

    /**
     * @brief 检查动画是否已完成
     * @return bool_t true表示已完成，false表示未完成
     */
    bool_t is_finished() const {
        return is_running_ && elapsed_time_ >= duration_;
    }

    /**
     * @brief 获取已过去的时间
     * @return float_t 已过去的时间
     */
    float_t elapsed_time() const { return elapsed_time_; }

    /**
     * @brief 设置已过去的时间
     * @param elapsed_time 要设置的已过去时间
     * @note 会自动处理边界情况，确保时间在有效范围内
     */
    void set_elapsed_time(float_t elapsed_time) {
        elapsed_time_ = elapsed_time;
        if (elapsed_time_ < 0.0f) {
            update_to(0.0f);
        } else if (elapsed_time_ > duration_) {
            update_to(duration_);
        }
    }

   public:
    /**
     * @brief 更新动画状态
     * @param dt 时间增量，默认为 kEpsilon
     * @note 纯虚函数，必须在子类中实现
     */
    virtual void update(float_t dt = kEpsilon) = 0;

    /**
     * @brief 更新到指定时间点
     * @param time 要更新的时间点
     */
    virtual void update_to(float_t time) {};

    /**
     * @brief 开始播放动画
     * @note 纯虚函数，必须在子类中实现
     */
    virtual void start() = 0;

    /**
     * @brief 暂停动画
     * @note 纯虚函数，必须在子类中实现
     */
    virtual void pause() = 0;

    /**
     * @brief 恢复播放动画
     * @note 纯虚函数，必须在子类中实现
     */
    virtual void resume() = 0;

    /**
     * @brief 停止动画
     * @note 纯虚函数，必须在子类中实现
     */
    virtual void stop() = 0;
};
}  // namespace xcal::animation
