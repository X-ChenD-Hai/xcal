#include <xcal/animation/Interpolation.hpp>
xcal::animation::ScalerInterpolation::ScalerInterpolation(
    property::Scalar* property, float_t start_value, float_t end_value,
    std::function<float_t(float_t)> interpolation_func)
    : AbsAnimation(),
      property_(property),
      start_value_(start_value),
      end_value_(end_value),
      interpolation_func_(std::move(interpolation_func)) {}
void xcal::animation::ScalerInterpolation::update_to(float_t time) {
    *property_ = start_value_ +
                 ((end_value_ - start_value_) * interpolation_func_(time));
}
