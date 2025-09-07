#pragma once
#include <xcal/property/core/property.hpp>
#include <xcmath/mobject/vec.hpp>
namespace xcal::property {
template <typename T, size_t N>
class XCAL_API Vec : public MProperty {
    XCAL_PROPERTY_TYPE(Vec)

   private:
    using data_t = xcmath::vec<T, N>;
    Proxy<data_t> value_{this, T{}};

   public:
    template <typename... Args>
        requires std::constructible_from<data_t, Args...>
    Vec(Args&&... args) : value_{this, std::forward<Args>(args)...} {}
    Vec(const Vec&) = delete;
    Vec(Vec&&) = delete;
    Vec& operator=(const Vec&) = delete;
    Vec& operator=(Vec&&) = delete;
    data_t& value() { return value_; }
    const data_t& value() const { return value_; }
    operator data_t&() { return value_; }
    operator const data_t&() const { return value_; }

    Vec& operator=(const data_t& v) {
        value_ = v;
        return *this;
    }
};
}  // namespace xcal::property