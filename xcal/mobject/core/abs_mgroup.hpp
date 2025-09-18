#pragma once
#include <xcal/public.h>

#include <vector>
#include <xcal/mobject/core/abs_mobject.hpp>
#include <xcal/mobject/core/mobject_types.hpp>
#include <xcal/property/core/property.hpp>
#include <xcmath/mobject/declaration.hpp>
template <class ...T>
class A : public T... {

};


namespace xcal::mobject {
class XCAL_API AbsMGroup {
   private:
    std::vector<AbsMObject_ptr> mobjects_{};

   public:
    const std::vector<AbsMObject_ptr> &mobjects() const { return mobjects_; }
    virtual xcmath::mat4<float_t> group_transform_matrix() const = 0;

   public:
    AbsMGroup(const AbsMGroup &) = delete;
    AbsMGroup(AbsMGroup &&) = default;
    AbsMGroup &operator=(const AbsMGroup &) = delete;
    AbsMGroup &operator=(AbsMGroup &&) = default;
};
}  // namespace xcal::mobject