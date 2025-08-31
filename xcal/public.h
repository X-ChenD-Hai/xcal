#pragma once
#define XCLOG_FILE_TRACK
#define XCLOG_LINE_TRACK
#define XCLOG_FUNCTION_TRACK
#include <xclogger/asynczmqlogsubmitstream.hpp>
#include <xclogger/logger.hpp>
#define XCAL_FATAL_LEVEL 4
#define XCAL_ERROR_LEVEL 3
#define XCAL_WARN_LEVEL 2
#define XCAL_INFO_LEVEL 1
#define XCAL_DEBUG_LEVEL 0

#define XCAL_DEBUG(role, label) XLOG(XCAL_DEBUG_LEVEL, role, label)
#define XCAL_FATAL(role, label) XLOG(XCAL_FATAL_LEVEL, role, label)
#define XCAL_ERROR(role, label) XLOG(XCAL_ERROR_LEVEL, role, label)
#define XCAL_WARN(role, label) XLOG(XCAL_WARN_LEVEL, role, label)
#define XCAL_INFO(role, label) XLOG(XCAL_INFO_LEVEL, role, label)
XCLOG_ENABLE_ASYNCZMQLOGSUBMITSTREAM("tcp://127.0.0.1:5553")

namespace xcal {
using float_t = float;
using bool_t = bool;
};  // namespace xcal