#pragma once
#include <xcal/property/core/property.hpp>
#include <xcmath/mobject/vec.hpp>

#include "xcal/public.h"

namespace xcal::property {
template <typename T, size_t N>
class XCAL_API Vec : public MProperty {
    XCAL_PROPERTY_TYPE(Vec)
   public:
    using data_t = xcmath::vec<T, N>;

   private:
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
    float_t x() const
        requires(N > 0)
    {
        return ((const data_t&)value_).x();
    }
    float_t y() const
        requires(N > 1)
    {
        return ((const data_t&)value_).y();
    }
    float_t z() const
        requires(N > 2)
    {
        return ((const data_t&)value_).z();
    }
    float_t& x()
        requires(N > 0)
    {
        return ((data_t&)value_).x();
    }
    float_t& y()
        requires(N > 1)
    {
        return ((data_t&)value_).y();
    }
    float_t& z()
        requires(N > 2)
    {
        return ((data_t&)value_).z();
    }
    operator data_t&() { return value_; }
    operator const data_t&() const { return value_; }

    Vec& operator=(const data_t& v) {
        value_ = v;
        return *this;
    }
};
}  // namespace xcal::property