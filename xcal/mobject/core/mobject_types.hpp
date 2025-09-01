#pragma once

namespace xcal::mobject {
enum class Type { Polygone, Circle, Line, Path, Rectangle, Ellipse, Unknown };
namespace xcal {
inline const char* to_string(Type type) {
    switch (type) {
        case Type::Polygone:
            return "Polygone";
        case Type::Circle:
            return "Circle";
        case Type::Line:
            return "Line";
        case Type::Path:
            return "Path";
        case Type::Rectangle:
            return "Rectangle";
        case Type::Ellipse:
            return "Ellipse";
        case Type::Unknown:
            return "Unknown";
        default:
            return "Unknown";
    }
}
}  // namespace xcal
class MObject;
class Polygone;
class Circle;
class Line;
class Path;
class Rectangle;
class Ellipse;

#define XCAL_MOBJECT_TYPE(type)                                \
    virtual Type type_() const override { return Type::type; } \
                                                               \
   public:                                                     \
    struct META_INFO {                                         \
        static constexpr auto type_name = #type;               \
    };                                                         \
                                                               \
   private:

}  // namespace xcal::mobject