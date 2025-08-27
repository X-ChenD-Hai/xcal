#include "./color.hpp"

xcal::mobject::property::Color xcal::mobject::property::Color::from_hex(
    const std::string &hex) {
    if (hex.size() != 7 || hex[0] != '#') return Color(0.0, 0.0, 0.0);
    uint32_t value = std::stoul(hex.substr(1), nullptr, 16);
    return from_hex(value);
}
xcal::mobject::property::Color xcal::mobject::property::Color::from_hex(
    uint32_t hex) {
    return Color(((hex >> 16) & 0xff) / 255.0, ((hex >> 8) & 0xff) / 255.0,
                 (hex & 0xff) / 255.0);
}

xcal::mobject::property::Color xcal::mobject::property::Color::from_name(
    const std::string &name) {
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
