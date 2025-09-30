#include <xcal/property/position_list.hpp>

template class XCAL_API xcal::property::_PositionList<
    xcmath::vec<float_t, 2>, xcal::property::Type::PositionList>;
template class XCAL_API xcal::property::_PositionList<
    xcmath::vec<float_t, 3>, xcal::property::Type::ThreeDPositionList>;
template class XCAL_API xcal::property::MProperty::Proxy<xcal::bool_t>;
