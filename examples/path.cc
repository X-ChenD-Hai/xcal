#include <cmath>
#include <cstddef>
#include <xcal/mobject/objects/path.hpp>
#include <xcal/render/impl/opengl/opengl_render.hpp>
#include <xcal/scene/scene.hpp>
#include <xcmath/mobject/function.hpp>

int main() {
    auto scene = std::make_unique<xcal::scene::Scene>();
    using namespace xcal::mobject;
    using namespace xcal::property;

    Path::data_t p(10);

    for (size_t i = 0; i < p.size(); ++i) {
        auto d = xcmath::radians(i * 360.0 / p.size());
        p[i] = xcmath::vec2<float_t>{(float_t)cos(d), (float_t)sin(d)} *
               ((i % 2) * 0.5f + 0.5f);
    }

    auto path = scene->add<Path>(Path::data_t{p}, false)
                    ->set_stroke_color({0, 1, 0, 1})
                    ->set_fill_color({0, 1, 1, 0.1});

    auto render = xcal::render::opengl::OpenGLRender{scene.get()};
    render.default_camera()
        ->set_background_color(0.2, 0.2, 0.2, 1.0)
        ->set_position(0, 0, 3);

    render.show(1200, 675);
    return 0;
}