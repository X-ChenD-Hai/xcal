#include <xcal/render/core/abs_render.hpp>
#define ROLE RENDER
#define LABEL ABSRENDER
#include <xcal/utils/logmacrohelper.inc>
template <typename ObjectPtr>
void xcal::render::AbsRender<ObjectPtr>::set_scene(Scene *scene) {
    _I("set scene: (" << scene << ")");
    scene_ = scene;
}

template class XCAL_API xcal::render::AbsRender<xcal::mobject::mobject_ptr>;