#include <public.h>

#include <render/impl/opengl/opengl_render.hpp>

int main(int argc, char **argv) {
    XCAL_INFO(XCAL, APP) << "app start";
    auto scene = std::make_unique<xcal::scene::Scene>();
    auto render = xcal::render::opengl::OpenGLRender(scene.get());
    render.show();
    XCAL_INFO(XCAL, APP) << "app end";
    return 0;
}