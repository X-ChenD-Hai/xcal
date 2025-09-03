#pragma once
#define XCLOG_FILE_TRACK
#define XCLOG_LINE_TRACK
#define XCLOG_FUNCTION_TRACK
#include <xclogger/logger.hpp>
#ifdef _WIN32
#include <xclogger/asynczmqlogsubmitstream.hpp>
XCLOG_ENABLE_ASYNCZMQLOGSUBMITSTREAM("tcp://127.0.0.1:5553")
#else
#include <xclogger/asyncostreamlogsubmitstream.hpp>
XCLOG_ENABLE_ASYNCSTREAMLOGSUBMITSTREAM();
#endif

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

namespace xcal {
using float_t = float;
using bool_t = bool;
};  // namespace xcal

#ifndef _STD
#define _STD ::std::
#endif
#ifdef XCAL_ENABLE_DYNAMIC_LIBRARY
    // 定义导出和导入宏
#    ifdef _WIN32
    // Windows平台
#        ifdef __GNUC__
    // 使用GCC编译器
#            define XCAL_EXPORT __attribute__((dllexport))
#            define XCAL_IMPORT __attribute__((dllimport))
#        else
    // 使用MSVC或其他Windows编译器
#            define XCAL_EXPORT __declspec(dllexport)
#            define XCAL_IMPORT __declspec(dllimport)
#        endif
#    else
    // 非Windows平台
#        if __GNUC__ >= 4
    // 使用GCC 4及以上版本
#            define XCAL_EXPORT __attribute__((visibility("default")))
#            define XCAL_IMPORT
#        else
    // 其他编译器
#            define XCAL_EXPORT
#            define XCAL_IMPORT
#        endif
#    endif

// 根据是否正在构建库来决定使用导出还是导入宏
#    ifdef XCAL_BUILD
#        define XCAL_API XCAL_EXPORT
#    else
#        define XCAL_API XCAL_IMPORT
#    endif
#else
#    define XCAL_API
#endif  // XCAL_ENABLE_DYNAMIC_LIBRARY
