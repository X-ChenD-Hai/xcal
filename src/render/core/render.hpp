#include <render/core/abs_render.hpp>

namespace xcal::render {
class Render : public AbsRender<mobject::mobject_ptr> {
   public:
    using AbsRender<mobject::mobject_ptr>::AbsRender;
};
}  // namespace xcal::render