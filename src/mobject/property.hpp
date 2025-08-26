#pragma once
#include <public.h>

#include <unordered_map>
#include <vector>

#define XCAL_PROPERTY_TYPE(type) \
    virtual Type type_() const override { return Type::type; }

namespace xcal::mobject::property {

enum class Type {
    Position,
    PositionList,
    ThreeDPosition,
    ThreeDPositionList,
    Scalar,
    Color,
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

class Scalar : public MProperty {
    XCAL_PROPERTY_TYPE(Scalar)
   private:
    Proxy<float_t> value_{0.0, this};

   public:
    Scalar() = default;
    Scalar(float_t value) { value_ = value; }
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

class Position : public MProperty {
    XCAL_PROPERTY_TYPE(Position)
   private:
    Proxy<std::array<float_t, 2>> data_{{0.0}, this};

   public:
    Position() = default;
    Position(float_t x, float_t y) { data_ = {{x, y}}; }
    Position(std::array<float_t, 2> list) { data_ = list; }
    const float_t &x() const { return data_[0]; }
    const float_t &y() const { return data_[1]; }
    float_t &x() { return data_[0]; }
    float_t &y() { return data_[1]; }
};

class ThreeDPosition : public Position {
    XCAL_PROPERTY_TYPE(ThreeDPosition)
   private:
    Proxy<float_t> z_ = {0.0, this};

   public:
    explicit ThreeDPosition() = delete;
    ThreeDPosition(float_t x, float_t y, float_t z) : Position(x, y) { z_ = z; }
    const float_t &z() const { return z_; }
    float_t &z() { return z_; }
};
template <typename __ItemType, Type __Type>
class _PositionList : public MProperty {
    virtual Type type_() const override { return __Type; }

   private:
    Proxy<std::vector<__ItemType>> positions_{std::vector<__ItemType>(), this};
    Proxy<bool_t> closed_{false, this};

   public:
    _PositionList() : _PositionList({}) {};
    template <typename... Args>
        requires(std::is_constructible_v<__ItemType, Args...>)
    _PositionList(const Args &...positions, bool closed = false) {
        positions_ = {__ItemType(positions)...};
        closed_ = closed;
    }
    const Proxy<bool_t> &closed() const { return closed_; }
    Proxy<bool_t> &closed() { return closed_; }
    const std::vector<__ItemType> &positions() const { return positions_; }
    std::vector<__ItemType> &positions() { return positions_; }
};

class Color : public MProperty {
    XCAL_PROPERTY_TYPE(Color)
   private:
    Proxy<std::array<float_t, 4>> data_ = {{0.0, 0.0, 0.0, 1.0}, this};

   public:
    Color() : MProperty() {}
    Color(float_t r, float_t g, float_t b, float_t a = 1.0) {
        data_ = {{r, g, b, a}};
    }
    const float_t &r() const { return data_[0]; }
    const float_t &g() const { return data_[1]; }
    const float_t &b() const { return data_[2]; }
    const float_t &a() const { return data_[3]; }
    float_t &r() { return data_[0]; }
    float_t &g() { return data_[1]; }
    float_t &b() { return data_[2]; }
    float_t &a() { return data_[3]; }

    size_t to_hex() {
        return ((size_t(data_[0] * 255) << 16) | (size_t(data_[1] * 255) << 8) |
                size_t(data_[2] * 255));
    }
    std::string to_hex_string() {
        return "#" + std::string(std::to_string(to_hex()));
    }
    static Color from_hex(uint32_t hex) {
        return Color(((hex >> 16) & 0xff) / 255.0, ((hex >> 8) & 0xff) / 255.0,
                     (hex & 0xff) / 255.0);
    }
    static Color from_name(const std::string &name) {
        if (name == "red")
            return Color(1.0, 0.0, 0.0);
        else if (name == "green")
            return Color(0.0, 1.0, 0.0);
        else if (name == "blue")
            return Color(0.0, 0.0, 1.0);
        else if (name == "white")
            return Color(1.0, 1.0, 1.0);
        else if (name == "black")
            return Color(0.0, 0.0, 0.0);
        else if (name == "yellow")
            return Color(1.0, 1.0, 0.0);
        else if (name == "cyan")
            return Color(0.0, 1.0, 1.0);
        else if (name == "magenta")
            return Color(1.0, 0.0, 1.0);
        else if (name == "gray")
            return Color(0.5, 0.5, 0.5);
        else
            return Color(0.0, 0.0, 0.0);
    }
    static Color from_hex(const std::string &hex) {
        if (hex.size() != 7 || hex[0] != '#') return Color(0.0, 0.0, 0.0);
        uint32_t value = std::stoul(hex.substr(1), nullptr, 16);
        return from_hex(value);
    }
};
using PositionList = _PositionList<Position, Type::PositionList>;
using ThreeDPositionList =
    _PositionList<ThreeDPosition, Type::ThreeDPositionList>;

}  // namespace xcal::mobject::property