#pragma once
#include <vector>
#include <xcal/property/core/property.hpp>
#include <xcal/property/position.hpp>

namespace xcal::property {

template <typename __ItemType, Type __Type>
class _PositionList : public MProperty {
    virtual Type type_() const override { return __Type; }

   private:
    Proxy<std::vector<__ItemType>> positions_{this, {}};
    Proxy<bool_t> closed_{this, false};

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

using PositionList = _PositionList<Position, Type::PositionList>;
using ThreeDPositionList =
    _PositionList<ThreeDPosition, Type::ThreeDPositionList>;

}  // namespace xcal::property
