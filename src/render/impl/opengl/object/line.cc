#include <render/impl/opengl/object/line.hpp>
#define ROLE OpenGLObject
#define LABEL Line
#include <utils/logmacrohelper.inc>
void xcal::render::opengl::object::Line::create() {
    _I("Create Line: " << mobject_);
};
void xcal::render::opengl::object::Line::destroy() {};
void xcal::render::opengl::object::Line::render() {};
xcal::render::opengl::object::Line::Line(mobject::Line* mobject)
    : mobject_(mobject) {
    _I("Create Line: " << this << " from mobject: " << mobject_);
};

XCAL_OPENGL_OBJECT_CREATER_HELPER(Line, mobject) {
    return std::make_unique<xcal::render::opengl::object::Line>(mobject);
}
