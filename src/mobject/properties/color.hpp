#pragma once
#include <mobject/core/property.hpp>
#include <array>
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
    static Color from_hex(uint32_t hex) {
        return Color(((hex >> 16) & 0xff) / 255.0, ((hex >> 8) & 0xff) / 255.0,
                     (hex & 0xff) / 255.0);
    }
    static Color from_name(const std::string &name) {
        if (name == "red")
            return Color(1.0, 0.0, 0.0);
        else if (name == "green")
            return Color(0.0, 1.0, 0.0);
        else if (name == "blue")
            return Color(0.0, 0.0, 1.0);
        else if (name == "white")
            return Color(1.0, 1.0, 1.0);
        else if (name == "black")
            return Color(0.0, 0.0, 0.0);
        else if (name == "yellow")
            return Color(1.0, 1.0, 0.0);
        else if (name == "cyan")
            return Color(0.0, 1.0, 1.0);
        else if (name == "magenta")
            return Color(1.0, 0.0, 1.0);
        else if (name == "gray")
            return Color(0.5, 0.5, 0.5);
        else
            return Color(0.0, 0.0, 0.0);
    }
    static Color from_hex(const std::string &hex) {
        if (hex.size() != 7 || hex[0] != '#') return Color(0.0, 0.0, 0.0);
        uint32_t value = std::stoul(hex.substr(1), nullptr, 16);
        return from_hex(value);
    }
};

}  // namespace xcal::mobject::property
