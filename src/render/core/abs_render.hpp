#pragma once
#include <scene/scene.hpp>
namespace xcal::render {
template <typename ObjectPtr = mobject::AbsMObject_ptr>
class AbsRender {
   private:
    scene::AbsScene<ObjectPtr> *scene_ = nullptr;

   public:
    explicit AbsRender(scene::AbsScene<ObjectPtr> *scene) : scene_(scene) {}
    virtual ~AbsRender() = default;
};
}  // namespace xcal::render