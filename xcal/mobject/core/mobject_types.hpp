#pragma once

#include <xcal/public.h>
namespace xcal::mobject {
enum class Type {
    Polygone,
    Axis,
    Axis3D,
    Circle,
    Line,
    Path,
    Rectangle,
    Ellipse,
    Unknown
};

class MObject;
class Polygone;
class Circle;
class Line;
class Path;
class Rectangle;
class Ellipse;

#define XCAL_MOBJECT_TYPE(type)                        \
    Type type_() const override { return Type::type; } \
                                                       \
   public:                                             \
    struct META_INFO {                                 \
        static constexpr auto type_name = #type;       \
    };                                                 \
                                                       \
   private:

}  // namespace xcal::mobject
namespace xcal {
XCAL_API inline const char* to_string(xcal::mobject::Type type) {
    using namespace xcal::mobject;
    switch (type) {
        case Type::Axis:
            return "Axis";
        case Type::Axis3D:
            return "Axis3D";
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