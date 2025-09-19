#pragma once
#include <xcal/public.h>

#include <xcal/property/core/property.hpp>

namespace xcal::property {

class XCAL_API Scalar : public MProperty {
    XCAL_PROPERTY_TYPE(Scalar)
   public:
    using data_t = float_t;

   private:
    Proxy<data_t> value_{this, 0.0f};

   public:
    Scalar() = default;
    explicit Scalar(data_t value) : value_(this, value) {}
    const data_t &value() const { return value_; }
    // NOLINTNEXTLINE(google-explicit-constructor)
    operator const data_t &() const { return value_; }
#define XCAL_SCALAR_OPERATOR(op)         \
    /* NOLINTNEXTLINE */                 \
    Scalar &operator op(float_t value) { \
        value_ op value;                 \
        return *this;                    \
    }
    XCAL_SCALAR_OPERATOR(+=)
    XCAL_SCALAR_OPERATOR(-=)
    XCAL_SCALAR_OPERATOR(*=)
    XCAL_SCALAR_OPERATOR(/=)
#undef XCAL_SCALAR_OPERATOR

    Scalar &operator=(float_t value) {
        value_ = value;
        return *this;
    }
};

}  // namespace xcal::property
