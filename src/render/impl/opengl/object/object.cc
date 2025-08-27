#include <glad/glad.h>
//
#include <mobject/mobject_all.hpp>
#include <render/impl/opengl/object/object.hpp>

xcal::render::opengl::object::Object::Object() {
    glGenBuffers(1, &id_);
    glBindVertexArray(id_);
};
xcal::render::opengl::object::Object::~Object() { glDeleteBuffers(1, &id_); };
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
