/**
 * @file timelinedriver.hpp
 * @author X_Chen D_Hai (illuminatestar@foxmail.com)
 * @brief
 * @version 0.1
 * @date 2025-09-09
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once
#include <xcal/public.h>

#include <xcal/animation/core/timeline.hpp>
namespace xcal::animation {

class XCAL_API TimelineDriver {
   public:
    TimelineDriver(const TimelineDriver &) = delete;
    TimelineDriver(TimelineDriver &&) = delete;
    TimelineDriver &operator=(const TimelineDriver &) = delete;
    TimelineDriver &operator=(TimelineDriver &&) = delete;
};

}  // namespace xcal::animation