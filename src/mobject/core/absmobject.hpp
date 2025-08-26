#pragma once
#include <public.h>

#include <mobject/core/mobject_types.hpp>
#include <mobject/core/property.hpp>

namespace xcal::mobject {
class AbsMObject {
   private:
    virtual Type type_() const = 0;

   private:
    bool_t visible_ = {true};
    std::vector<property::MProperty*> properties_{};

   protected:
    template <class... Arg>
        requires(std::is_base_of_v<property::MProperty, Arg> && ...)
    void register_properties(Arg&... arg) {
        (properties_.push_back(static_cast<property::MProperty*>(&arg)), ...);
    }

   public:
    AbsMObject() = default;

   public:
    bool visible() const { return visible_; }
    bool& visible() { return visible_; }
    std::vector<property::MProperty*>& properties() { return properties_; }
    virtual ~AbsMObject() = default;
};
using AbsMObject_ptr = std::unique_ptr<AbsMObject>;
};  // namespace xcal::mobject