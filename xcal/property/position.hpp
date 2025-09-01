#pragma once
#include <xcal/property/core/property.hpp>
#include <xcmath/xcmath.hpp>

#include "xcmath/mobject/vec.hpp"

namespace xcal::property {

class Position : public MProperty {
    XCAL_PROPERTY_TYPE(Position)
   public:
    using vec = xcmath::vec<float_t, 2>;
    using MProxy = MProperty::Proxy<vec>;

   private:
    MProxy data_{this, {0.0f}};

   public:
    Position() = default;
    Position(float_t x, float_t y) : data_(this, {x, y}) { data_ = {{x, y}}; }
    Position(xcmath::vec<float_t, 2> list) { data_ = list; }
    const float_t &x() const { return data_[0]; }
    const float_t &y() const { return data_[1]; }
    float_t &x() { return data_[0]; }
    float_t &y() { return data_[1]; }
    const vec &data() const { return data_; }
    vec &data() { return data_; }
};

class ThreeDPosition : public Position {
    XCAL_PROPERTY_TYPE(ThreeDPosition)
   private:
    Proxy<float_t> z_ = {this, 0.0};

   public:
    explicit ThreeDPosition() = delete;
    ThreeDPosition(float_t x, float_t y, float_t z) : Position(x, y) { z_ = z; }
    const float_t &z() const { return z_; }
    float_t &z() { return z_; }
};

}  // namespace xcal::property
