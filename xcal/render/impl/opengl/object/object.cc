#include <xcal/render/impl/opengl/utils/glbindingincludehelper.inc>
//
#include <xcal/mobject/mobject_all.hpp>
#include <xcal/render/impl/opengl/object/line.hpp>
#include <xcal/render/impl/opengl/object/object.hpp>

#define ROLE OpenGLRender
#define LABEL Object
#include <xcal/utils/logmacrohelper.inc>
xcal::render::opengl::object::Object::Object() {

};
template <class T>
    requires std::is_base_of_v<xcal::mobject::MObject, T>
xcal::render::opengl::object::object_ptr xcal::render::opengl::object::create(
    T* mobject) {
    _E("UnImplemented MObject type: " << T::META_INFO::type_name);
    return nullptr;
}
xcal::render::opengl::object::Object::~Object() {};
xcal::render::opengl::object::object_ptr xcal::render::opengl::object::create(
    xcal::mobject::MObject* mobject) {
    switch (mobject->type()) {
        case xcal::mobject::Type::Polygone:
            return create<xcal::mobject::Polygone>(
                (xcal::mobject::Polygone*)mobject);
        case xcal::mobject::Type::Circle:
            return create<xcal::mobject::Circle>(
                (xcal::mobject::Circle*)mobject);
        case xcal::mobject::Type::Line:
            return create<xcal::mobject::Line>((xcal::mobject::Line*)mobject);
        case xcal::mobject::Type::Path:
            return create<xcal::mobject::Path>((xcal::mobject::Path*)mobject);
        case xcal::mobject::Type::Rectangle:
            return create<xcal::mobject::Rectangle>(
                (xcal::mobject::Rectangle*)mobject);
        case xcal::mobject::Type::Ellipse:
            return create<xcal::mobject::Ellipse>(
                (xcal::mobject::Ellipse*)mobject);
        default:
            return nullptr;
    }
}
