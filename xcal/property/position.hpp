#pragma once
#include <xcal/property/core/property.hpp>
#include <xcmath/xcmath.hpp>

#include "xcmath/mobject/vec.hpp"

namespace xcal::property {

class XCAL_API Position : public MProperty {
    XCAL_PROPERTY_TYPE(Position)
   public:
    using data_t = xcmath::vec<float_t, 2>;
    using MProxy = MProperty::Proxy<data_t>;

   private:
    MProxy data_{this, {0.0f}};

   public:
    Position() = default;
    Position(const Position &) = delete;
    Position(Position &&) = delete;
    Position &operator=(const Position &) = delete;
    Position &operator=(Position &&) = delete;
    Position(float_t x, float_t y) : data_(this, {x, y}) { data_ = {{x, y}}; }
    explicit Position(xcmath::vec<float_t, 2> list) { data_ = list; }
    const float_t &x() const { return data_[0]; }
    const float_t &y() const { return data_[1]; }
    float_t &x() { return data_[0]; }
    float_t &y() { return data_[1]; }
    const data_t &value() const { return data_; }
    data_t &value() { return data_; }
    Position &operator=(const data_t &v) {
        data_ = v;
        return *this;
    }
};

class XCAL_API ThreeDPosition : public Position {
    XCAL_PROPERTY_TYPE(ThreeDPosition)
    using data_t = xcmath::vec<float_t, 3>;

   private:
    Proxy<float_t> z_{this, 0.0};

   public:
    explicit ThreeDPosition() = delete;
    ThreeDPosition(const ThreeDPosition &) = delete;
    ThreeDPosition(ThreeDPosition &&) = delete;
    ThreeDPosition &operator=(const ThreeDPosition &) = delete;
    ThreeDPosition &operator=(ThreeDPosition &&) = delete;
    ThreeDPosition(float_t x, float_t y, float_t z) : Position(x, y) { z_ = z; }
    const float_t &z() const { return z_; }
    float_t &z() { return z_; }
    ThreeDPosition &operator=(const data_t &v) {
        *(Position *)this = v.xy();
        z_ = v[2];
        return *this;
    }
};

}  // namespace xcal::property
