#include <xcal/public.h>

#include <memory>
#include <xcal/animation/Interpolation.hpp>
#include <xcal/animation/core/timeline.hpp>
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
    using namespace xcal::animation;

    // XCAL_INFO(XCAL, APP) << "cc pos: " << cc->pos().value();
    auto l1 =
        scene->add<Line>(3)->set_pos({0, 0})->set_stroke_color({1, 0, 0, 5});
    auto c1 = scene->add<Circle>();
    c1->set_radius(1.f / 2)
        ->set_stroke_color({0.5, 0, 0.5})
        ->translate(0, 1)
        ->scale(0.5);
    auto c2 = scene->add<Circle>()->set_radius(0.5f / 2)->set_stroke_color(
        {0, 0.5, 0.5});
    auto l2 = scene->add<Line>(2)->set_stroke_color({0, 0, 1})->rotate(45);
    auto l3 = scene->add<Line>(2)->set_stroke_color({0, 1, 0})->rotate(90);
    scene->add<PerspectiveCamera>(45.0, 16 / 9.0, 0.1, 1000.0)
        ->set_position(0, 0, 3)
        ->set_target(0, 0, 0);
    auto ani = scene->add<ScalerInterpolation>(&c1->scale_x(), 0, 1,
                                               interpolation_functions::linear);
    scene->add<Timeline>();

    auto render = xcal::render::opengl::OpenGLRender{scene.get()};
    render.default_camera()
        ->set_background_color(0.2, 0.2, 0.2, 1.0)
        ->set_position(0, 0, 3);

    render.show(1200, 675);
    XCAL_INFO(XCAL, APP) << "app end";
    return 0;
}
