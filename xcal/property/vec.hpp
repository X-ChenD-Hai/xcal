#pragma once
#include <xcal/property/core/property.hpp>
#include <xcmath/mobject/vec.hpp>
namespace xcal::property {
template <typename T, size_t N>
class Vec : public MProperty {
    XCAL_PROPERTY_TYPE(Vec)

   private:
    using VecType = xcmath::vec<T, N>;
    Proxy<VecType> value_{this, T{}};

   public:
    template <typename... Args>
        requires std::constructible_from<VecType, Args...>
    Vec(Args&&... args) : value_{this, std::forward<Args>(args)...} {}
    VecType& value() { return value_; }
    const VecType& value() const { return value_; }
    operator VecType&() { return value_; }
    operator const VecType&() const { return value_; }
};
}  // namespace xcal::property