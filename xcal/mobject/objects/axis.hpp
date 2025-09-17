#pragma once
#include <xcal/public.h>

#include <xcal/mobject/core/mobject.hpp>
#include <xcal/property/scalar.hpp>

namespace xcal::mobject {
class XCAL_API Axis : public MObject {
    XCAL_MOBJECT_TYPE(Axis)
    property::Scalar min_x_;
    property::Scalar max_x_;
    property::Scalar x_tick_size_;
    property::Scalar min_y_;
    property::Scalar max_y_;
    property::Scalar y_tick_size_;

   public:
    Axis(float_t min_x = -1, float_t max_x = 1, float_t x_tick_size = 1,
         float_t min_y = -1, float_t max_y = 1, float_t y_tick_size = 1)
        : min_x_(min_x),
          max_x_(max_x),
          x_tick_size_(x_tick_size),
          min_y_(min_y),
          max_y_(max_y),
          y_tick_size_(y_tick_size) {}

    float_t min_x() const { return min_x_.value(); }
    float_t max_x() const { return max_x_.value(); }
    float_t x_tick_size() const { return x_tick_size_.value(); }
    float_t min_y() const { return min_y_.value(); }
    float_t max_y() const { return max_y_.value(); }
    float_t y_tick_size() const { return y_tick_size_.value(); }
};
class XCAL_API Axis3D : public MObject {
    XCAL_MOBJECT_TYPE(Axis3D)
    property::Scalar min_x_;
    property::Scalar max_x_;
    property::Scalar x_tick_size_;
    property::Scalar min_y_;
    property::Scalar max_y_;
    property::Scalar y_tick_size_;
    property::Scalar min_z_;
    property::Scalar max_z_;
    property::Scalar z_tick_size_;

   public:
    Axis3D(float_t min_x = -1, float_t max_x = 1, float_t x_tick_size = 1,
           float_t min_y = -1, float_t max_y = 1, float_t y_tick_size = 1,
           float_t min_z = -1, float_t max_z = 1, float_t z_tick_size = 1)
        : min_x_(min_x),
          max_x_(max_x),
          x_tick_size_(x_tick_size),
          min_y_(min_y),
          max_y_(max_y),
          y_tick_size_(y_tick_size),
          min_z_(min_z),
          max_z_(max_z),
          z_tick_size_(z_tick_size) {}

    float_t min_x() const { return min_x_.value(); }
    float_t max_x() const { return max_x_.value(); }
    float_t x_tick_size() const { return x_tick_size_.value(); }
    float_t min_y() const { return min_y_.value(); }
    float_t max_y() const { return max_y_.value(); }
    float_t y_tick_size() const { return y_tick_size_.value(); }
    float_t min_z() const { return min_z_.value(); }
    float_t max_z() const { return max_z_.value(); }
    float_t z_tick_size() const { return z_tick_size_.value(); }
};

}  // namespace xcal::mobject