#pragma once
#include <mobject/core/property.hpp>
#include <array>

namespace xcal::mobject::property {

class Position : public MProperty {
    XCAL_PROPERTY_TYPE(Position)
   private:
    Proxy<std::array<float_t, 2>> data_{{0.0}, this};

   public:
    Position() = default;
    Position(float_t x, float_t y) { data_ = {{x, y}}; }
    Position(std::array<float_t, 2> list) { data_ = list; }
    const float_t &x() const { return data_[0]; }
    const float_t &y() const { return data_[1]; }
    float_t &x() { return data_[0]; }
    float_t &y() { return data_[1]; }
};

class ThreeDPosition : public Position {
    XCAL_PROPERTY_TYPE(ThreeDPosition)
   private:
    Proxy<float_t> z_ = {0.0, this};

   public:
    explicit ThreeDPosition() = delete;
    ThreeDPosition(float_t x, float_t y, float_t z) : Position(x, y) { z_ = z; }
    const float_t &z() const { return z_; }
    float_t &z() { return z_; }
};

}  // namespace xcal::mobject::property
