#include <xcal/public.h>

#include <memory>
#include <xcal/camera/perspectivecamera.hpp>
#include <xcal/mobject/mobject_all.hpp>
#include <xcal/mobject/objects/circle.hpp>
#include <xcal/render/impl/opengl/opengl_render.hpp>
#include <xcmath/utils/show.hpp>

int main(int argc, char **argv) {
    XCAL_INFO(XCAL, APP) << "app start";
    auto scene = std::make_unique<xcal::scene::Scene>();
    using namespace xcal::mobject;
    using namespace xcal::camera;

    // XCAL_INFO(XCAL, APP) << "cc pos: " << cc->pos().value();
    scene->add<Line>(3)->set_pos({0, 0})->set_stroke_color({1, 0, 0, 5});
    auto cc = scene->add<Circle>()->set_radius(1.f / 2)->set_stroke_color(
        {0.5, 0, 0.5});
    scene->add<Circle>()->set_radius(0.5f / 2)->set_stroke_color({0, 0.5, 0.5});
    scene->add<Line>(2)->set_stroke_color({0, 0, 1})->rotate(45);
    scene->add<Line>(2)->set_stroke_color({0, 1, 0})->rotate(90);
    auto c = scene
                 ->add(std::make_unique<PerspectiveCamera>(45.0, 16 / 9.0, 0.1,
                                                           1000.0))
                 ->set_position(0, 0, 3)
                 ->set_target(0, 0, 0);
    auto render = xcal::render::opengl::OpenGLRender{scene.get()};
    render.aspect() = 16 / 9.0;
    render.background_color() = xcmath::vec4<float_t>{0.2, 0.2, 0.2, 1.0};
    render.show(1200, 675);
    XCAL_INFO(XCAL, APP) << "app end";
    return 0;
}
