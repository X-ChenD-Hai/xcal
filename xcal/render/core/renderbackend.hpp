#pragma once
#include <xcal/scene/core/scene.hpp>
namespace xcal::render {
class RenderBackend {
   public:
    virtual void set_scene(scene::Scene* scene) = 0;
    virtual void new_frame() {};
    virtual void render() {};
    virtual void end_frame() {};
    virtual ~RenderBackend() = default;
};
}  // namespace xcal::render