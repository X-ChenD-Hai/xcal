/**
 * @file Interpolation.hpp
 * @author X_Chen D_Hai (illuminatestar@foxmail.com)
 * @brief
 * @version 0.1
 * @date 2025-09-09
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once
#include <xcal/public.h>

#include <xcal/animation/core/abs_animation.hpp>
#include <xcal/animation/interpolation_functions.hpp>
#include <xcal/property/scalar.hpp>

#include "interpolation_functions.hpp"

namespace xcal::property {
class Scalar;
}
namespace xcal::animation {

class XCAL_API ScalerInterpolation : AbsAnimation {
   private:
    property::Scalar* property_;
    float_t start_value_;
    float_t end_value_;
    std::function<float_t(float_t)> interpolation_func_;

   public:
    ScalerInterpolation(property::Scalar* property, float_t start_value,
                        float_t end_value,
                        std::function<float_t(float_t)> interpolation_func =
                            interpolation_functions::linear)
        : AbsAnimation(),
          property_(property),
          start_value_(start_value),
          end_value_(end_value),
          interpolation_func_(std::move(interpolation_func)) {}
    bool update(float_t time) {
        if (property_ == nullptr || interpolation_func_ == nullptr ||
            time < 0.0f)
            return false;
        *property_ = (end_value_ - start_value_) *
                     (interpolation_func_(time / duration()));
        return true;
    }
    /**
     * @brief 更新到指定时间点
     * @param time 要更新的时间点
     */
    virtual void update_to(float_t time) override { update(time); }
};
}  // namespace xcal::animation