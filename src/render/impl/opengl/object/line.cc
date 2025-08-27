#include <render/impl/opengl/object/line.hpp>

void xcal::render::opengl::object::Line::create() {};
void xcal::render::opengl::object::Line::destroy() {};
void xcal::render::opengl::object::Line::render() {};
xcal::render::opengl::object::Line::Line(mobject::Line* mobject)
    : mobject_(mobject) {};

XCAL_OPENGL_OBJECT_CREATER_HELPER(Line, mobject) {
    return std::make_unique<xcal::render::opengl::object::Line>(mobject);
}
