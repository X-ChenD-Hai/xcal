
#pragma once

#include <xcal/public.h>

#include <xcal/mobject/core/mobject.hpp>

namespace xcal::render::opengl {
class OpenGLRender;
}
namespace xcal::render::opengl::ui {
class UIRender {
    struct ObjectHandle {
        using mobject_t = xcal::mobject::MObject;
        xcal::bool_t changed = false;
        mobject_t* obj;
        std::string name;
        std::string type;
        float_t x, y;
        float_t depth;
        ObjectHandle(mobject_t* obj);
    };

    bool show = true;
    std::vector<ObjectHandle> object_handles{};
    OpenGLRender* renderer{nullptr};
    float_t tmp;

   public:
    UIRender(OpenGLRender* renderer) : renderer(renderer) {}
    void init();
    void deinit();
    void flush();
    void render_obj(ObjectHandle& obj, int id);
    void render();
    void render_ui();
    void before_swap_buffers();
};
}  // namespace xcal::render::opengl::ui