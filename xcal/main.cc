#include <xcal/public.h>

#include <xcal/mobject/mobject_all.hpp>
#include <xcal/mobject/objects/circle.hpp>
#include <xcal/render/impl/opengl/opengl_render.hpp>

int main(int argc, char **argv) {
    XCAL_INFO(XCAL, APP) << "app start";
    auto scene = std::make_unique<xcal::scene::Scene>();
    using namespace xcal::mobject;

    scene->add<Circle>()->set_stroke_color({0, 0.5, 0.5});
    scene->add<Line>(2)->set_stroke_color({1, 0, 0});
    scene->add<Line>(2)->set_stroke_color({0, 1, 0})->rotate(90);
    auto render = xcal::render::opengl::OpenGLRender(scene.get());
    render.show();
    XCAL_INFO(XCAL, APP) << "app end";
    return 0;
}