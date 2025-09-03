#pragma once
#include <xcal/property/core/property.hpp>
#include <xcmath/mobject/vec.hpp>
namespace xcal::property {
template <typename T, size_t N>
class XCAL_API Vec : public MProperty {
    XCAL_PROPERTY_TYPE(Vec)

   private:
    using vec = xcmath::vec<T, N>;
    Proxy<vec> value_{this, T{}};

   public:
    template <typename... Args>
        requires std::constructible_from<vec, Args...>
    Vec(Args&&... args) : value_{this, std::forward<Args>(args)...} {}
    vec& value() { return value_; }
    const vec& value() const { return value_; }
    operator vec&() { return value_; }
    operator const vec&() const { return value_; }
};
}  // namespace xcal::property