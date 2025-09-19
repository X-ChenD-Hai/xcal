#pragma once
#include <xcal/public.h>

#include <vector>
#include <xcal/mobject/core/abs_mobject.hpp>
#include <xcal/mobject/core/composedmobject.hpp>
#include <xcal/mobject/core/mobject_types.hpp>
#include <xcal/property/core/property.hpp>
#include <xcmath/mobject/declaration.hpp>

template <class... T>
class A : public T... {};

namespace xcal::mobject {
class XCAL_API AbsMGroup
    : public ComposedMObject<AbsMGroup, BaseTransformableMobject> {
   protected:
    std::vector<AbsMObject_ptr> mobjects_{};

   public:
    const std::vector<AbsMObject_ptr> &mobjects() const { return mobjects_; }
    AbsMGroup() : ComposedMObject{} {}

   public:
    AbsMGroup(const AbsMGroup &) = delete;
    AbsMGroup &operator=(const AbsMGroup &) = delete;
};
}  // namespace xcal::mobject