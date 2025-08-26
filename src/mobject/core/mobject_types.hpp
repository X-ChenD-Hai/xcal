#pragma once

namespace xcal::mobject {
enum class Type {
    Polygone,
    Circle,
    Line,
    Path,
    Rectangle,
    Ellipse,
};
#define XCAL_MOBJECT_TYPE(type) \
    virtual Type type_() const override { return Type::type; }

}  // namespace xcal::mobject