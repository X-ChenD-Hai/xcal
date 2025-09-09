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
 * @brief 抽象动画基类
 *
 * 提供动画基础功能，包括播放控制、时间管理和状态跟踪。
 * 所有具体动画类都应该继承自此类。
 */
class XCAL_API AbsAnimation {
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
     * @brief 更新到指定时间点
     * @param time 要更新的时间点 (between 0 and 1)
     */
    virtual void update_to(float_t time) = 0;

   public:
    AbsAnimation(const AbsAnimation&) = default;
    AbsAnimation(AbsAnimation&&) = delete;
    AbsAnimation& operator=(const AbsAnimation&) = default;
    AbsAnimation& operator=(AbsAnimation&&) = delete;
};
struct XCAL_API AnimationHandle {
    AbsAnimation* animation;
    float_t start_time;
    float_t duration;
};
}  // namespace xcal::animation
