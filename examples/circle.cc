#include <xcal/render/impl/opengl/opengl_render.hpp>
#include <xcal/scene/scene.hpp>

int main() {
    auto scene = std::make_unique<xcal::scene::Scene>();
    using namespace xcal::mobject;
    auto circle = scene->add<Circle>();
    circle->set_radius(1.f / 2)
        ->set_stroke_color({0.5, 0, 0.5})
        ->translate(0, 1)
        ->scale(0.5);
    auto render = xcal::render::opengl::OpenGLRender{scene.get()};
    render.default_camera()
        ->set_background_color(0.2, 0.2, 0.2, 1.0)
        ->set_position(0, 0, 3);

    render.show(1200, 675);
    return 0;
}