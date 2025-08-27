#pragma once
#include <array>
#include <mobject/core/property.hpp>
#include <string>

namespace xcal::mobject::property {

class Color : public MProperty {
    XCAL_PROPERTY_TYPE(Color)
   private:
    Proxy<std::array<float_t, 4>> data_ = {{0.0, 0.0, 0.0, 1.0}, this};

   public:
    Color() : MProperty() {}
    Color(float_t r, float_t g, float_t b, float_t a = 1.0) {
        data_ = {{r, g, b, a}};
    }
    const float_t &r() const { return data_[0]; }
    const float_t &g() const { return data_[1]; }
    const float_t &b() const { return data_[2]; }
    const float_t &a() const { return data_[3]; }
    float_t &r() { return data_[0]; }
    float_t &g() { return data_[1]; }
    float_t &b() { return data_[2]; }
    float_t &a() { return data_[3]; }

    size_t to_hex() {
        return ((size_t(data_[0] * 255) << 16) | (size_t(data_[1] * 255) << 8) |
                size_t(data_[2] * 255));
    }
    std::string to_hex_string() {
        return "#" + std::string(std::to_string(to_hex()));
    }
    static Color from_hex(uint32_t hex);
    static Color from_name(const std::string &name);
    static Color from_hex(const std::string &hex);
};

}  // namespace xcal::mobject::property
