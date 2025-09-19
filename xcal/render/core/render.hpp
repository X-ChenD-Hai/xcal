#pragma once
#include <xcal/mobject/core/abs_mobject.hpp>
#include <xcal/render/core/abs_render.hpp>

namespace xcal::render {
class XCAL_API Render : public AbsRender<mobject::AbsMObject_ptr> {
   public:
    using AbsRender::AbsRender;
};
}  // namespace xcal::render