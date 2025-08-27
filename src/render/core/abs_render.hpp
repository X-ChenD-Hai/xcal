#pragma once
#include <mobject/properties/time_duration.hpp>
#include <mobject/properties/time_point.hpp>
#include <scene/scene.hpp>

namespace xcal::render {
template <typename ObjectPtr = mobject::AbsMObject_ptr>
class AbsRender {
   private:
    scene::AbsScene<ObjectPtr> *scene_ = nullptr;

   public:
    using Scene = scene::AbsScene<ObjectPtr>;

   public:
    explicit AbsRender(scene::AbsScene<ObjectPtr> *scene) : scene_(scene) {}
    virtual ~AbsRender() = default;
};
}  // namespace xcal::render