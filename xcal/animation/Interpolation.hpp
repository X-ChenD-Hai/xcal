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
#include <xcal/animation/core/interpolation_functions.hpp>
#include <xcal/property/scalar.hpp>

namespace xcal::property {
class Scalar;
}
namespace xcal::animation {

class XCAL_API ScalerInterpolation : public AbsAnimation {
   private:
    property::Scalar* property_;
    float_t start_value_;
    float_t end_value_;
    std::function<float_t(float_t)> interpolation_func_;

   public:
    ScalerInterpolation(property::Scalar* property, float_t start_value,
                        float_t end_value,
                        std::function<float_t(float_t)> interpolation_func =
                            interpolation_functions::linear);
    ~ScalerInterpolation() override = default;

   public:
    void update_to(float_t time) override;

   public:
    ScalerInterpolation(const ScalerInterpolation&) = default;
    ScalerInterpolation(ScalerInterpolation&&) = delete;
    ScalerInterpolation& operator=(const ScalerInterpolation&) = default;
    ScalerInterpolation& operator=(ScalerInterpolation&&) = delete;
};
}  // namespace xcal::animation