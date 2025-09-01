#pragma once
#include <xcal/property/core/property.hpp>

namespace xcal::property {

class Scalar : public MProperty {
    XCAL_PROPERTY_TYPE(Scalar)
   private:
    Proxy<float_t> value_{this, 0.0f};

   public:
    Scalar() = default;
    Scalar(float_t value) : value_(this, value) {}
    const float_t &value() const { return value_; }
    operator const float_t &() const { return value_; }
#define XCAL_SCALAR_OPERATOR(op)         \
    Scalar &operator op(float_t value) { \
        value_ op value;                 \
        return *this;                    \
    }
    XCAL_SCALAR_OPERATOR(+=)
    XCAL_SCALAR_OPERATOR(-=)
    XCAL_SCALAR_OPERATOR(*=)
    XCAL_SCALAR_OPERATOR(/=)
#undef XCAL_SCALAR_OPERATOR
};

}  // namespace xcal::property
