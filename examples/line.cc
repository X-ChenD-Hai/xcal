#include <frontends/window/glfw/glfwrender.hpp>
#include <renderers/opengl/openglrender.hpp>
//
#include <xcal/mobject/objects/line.hpp>
#include <xcal/scene/scene.hpp>
#include <xcmath/mobject/function.hpp>

int main() {
    auto scene = std::make_unique<xcal::scene::Scene>();
    using namespace xcal::mobject;
    using namespace xcal::property;

    scene->add<Line>(1)->set_stroke_color({0.0, 0.0, 1.0, 1.0})->rotate(90);
    scene->add<Line>(1)->set_stroke_color({0.0, 1.0, 1.0, 1.0});
    scene->add<Line>(1)->set_stroke_color({1.0, 1.0, 1.0, 1.0})->rotate(45);
    scene->add<Line>(2)
        ->set_stroke_color({1.0, 1.0, 1.0, 1.0})
        ->rotate(135)
        ->scale(1);

    auto render = xcal::render::OpenGLRender{scene.get()};
    render.default_camera()
        ->set_background_color(0.2, 0.2, 0.2, 1.0)
        ->set_position(0, 0, 3);

    xcal::render::GLFWRender(&render).show(1200, 675);
    return 0;
}