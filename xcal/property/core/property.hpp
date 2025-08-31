#pragma once
#include <xcal/public.h>

#include <unordered_map>

#define XCAL_PROPERTY_TYPE(type) \
    virtual Type type_() const override { return Type::type; }

namespace xcal::property {

enum class Type {
    Position,
    PositionList,
    ThreeDPosition,
    ThreeDPositionList,
    Scalar,
    Color,
    TimeDuration,
    TimePoint,
    User,
};

class MProperty {
    virtual Type type_() const = 0;

   private:
    bool_t is_changed_{true};

   protected:
    template <typename T>
    class Proxy {
       private:
        T value_;
        static std::unordered_map<void *, MProperty *> proxy_to_self_;

       public:
        template <typename... Args>
            requires(std::is_constructible_v<T, Args...>)
        Proxy(Args &&...args, MProperty *self)
            : value_(std::forward<Args>(args)...) {
            proxy_to_self_[this] = self;
        }

        Proxy(T &&value, MProperty *self) : value_(std::move(value)) {
            proxy_to_self_[this] = self;
        }
        Proxy(const T &value, MProperty *self) : value_(value) {
            proxy_to_self_[this] = self;
        }
        void on_changed() {
            if (auto it = proxy_to_self_.find(this);
                it != proxy_to_self_.end()) {
                it->second->set_changed();
            }
        }
        Proxy &operator=(const T &value) {
            value_ = value;
            on_changed();
            return *this;
        }
        Proxy &operator=(T &&value) {
            value_ = std::move(value);
            on_changed();
            return *this;
        }
        Proxy(const Proxy &other) { value_ = other.value_; }
        Proxy(Proxy &&other) { value_ = std::move(other.value_); }
        Proxy &operator=(const Proxy &other) {
            value_ = other.value_;
            on_changed();
            return *this;
        }
        Proxy &operator=(Proxy &&other) {
            value_ = std::move(other.value_);
            on_changed();
            return *this;
        }
        operator T &() {
            on_changed();
            return value_;
        }
        operator const T &() const { return value_; }

        template <typename... Args>
        auto &operator[](Args &&...args) {
            on_changed();
            return value_[std::forward<Args>(args)...];
        }
        template <typename... Args>
        auto &operator[](Args &&...args) const {
            return value_[std::forward<Args>(args)...];
        }
        template <typename... Args>
        auto &operator()(Args &&...args) {
            on_changed();
            return value_(std::forward<Args>(args)...);
        }
        template <typename... Args>
        const auto &operator()(Args &&...args) const {
            return value_(std::forward<Args>(args)...);
        }
#define XCAL_PROPERTY_PROXY_OPERATOR(op) \
    template <typename Arg>              \
    auto &operator op(const Arg & arg) { \
        on_changed();                    \
        value_ op arg;                   \
        return *this;                    \
    }
        XCAL_PROPERTY_PROXY_OPERATOR(+=)
        XCAL_PROPERTY_PROXY_OPERATOR(-=)
        XCAL_PROPERTY_PROXY_OPERATOR(*=)
        XCAL_PROPERTY_PROXY_OPERATOR(/=)
        XCAL_PROPERTY_PROXY_OPERATOR(%=)
        XCAL_PROPERTY_PROXY_OPERATOR(^=)
        XCAL_PROPERTY_PROXY_OPERATOR(|=)
        XCAL_PROPERTY_PROXY_OPERATOR(&=)
        XCAL_PROPERTY_PROXY_OPERATOR(<<=)
        XCAL_PROPERTY_PROXY_OPERATOR(>>=)
#undef XCAL_PROPERTY_PROXY_OPERATOR
    };

   public:
    bool_t is_changed() const { return is_changed_; }
    void set_changed() { is_changed_ = true; }
    void reset_changed() { is_changed_ = false; }
    Type type() const { return type_(); };
    virtual ~MProperty() = default;
};
template <typename T>
std::unordered_map<void *, MProperty *> MProperty::Proxy<T>::proxy_to_self_{};

}  // namespace xcal::property
