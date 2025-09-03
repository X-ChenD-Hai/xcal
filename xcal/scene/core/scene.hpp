#pragma once
#include <xcal/mobject/mobject.hpp>
#include <xcal/scene/core/abs_scene.hpp>

namespace xcal::scene {

class XCAL_API Scene : public AbsScene<mobject::mobject_ptr> {
    // 现在mobjects()直接返回std::vector<mobject::mobject_ptr>&
    // 不需要类型转换，继承自模板基类
};

}  // namespace xcal::scene
