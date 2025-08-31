#pragma once
#include <xcal/public.h>

#include <memory>
#include <xcal/mobject/core/mobject.hpp>
#include <xcal/render/impl/opengl/core/typedef.hpp>
#include <xcal/render/impl/opengl/gl/vertexarrayobject.hpp>


namespace xcal::render::opengl {
class OpenGLRender;
}
namespace xcal::render::opengl::object {
class Object {
    friend class xcal::render::opengl::OpenGLRender;

   private:
    GL::VertexArrayObject vao_;

   protected:
    virtual void create() = 0;
    virtual void destroy() = 0;
    virtual void render() = 0;

    GL::VertexArrayObject& vao() { return vao_; }

   public:
    Object();
    virtual ~Object();
};

using object_ptr = std::unique_ptr<Object>;

template <class T>
    requires std::is_base_of_v<mobject::MObject, T>
xcal::render::opengl::object::object_ptr create(T* mobject);

object_ptr create(mobject::MObject* mobject);
}  // namespace xcal::render::opengl::object
#define XCAL_OPENGL_OBJECT_CREATER_HELPER(type, mobj)          \
    template <>                                                \
    xcal::render::opengl::object::object_ptr                   \
    xcal::render::opengl::object::create<xcal::mobject::type>( \
        xcal::mobject::type * mobj)