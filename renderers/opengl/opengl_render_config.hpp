#pragma once
#include <xcal/public.h>
#if defined(XCAL_ENABLE_DYNAMIC_LIBRARY) || \
    defined(XCAL_CODEC_ENABLE_DYNAMIC_LIBRARY)
// 定义导出和导入宏
#    ifdef _WIN32
// Windows平台
#        ifdef __GNUC__
// 使用GCC编译器
#            define XCAL_OPENGL_RENDERER_EXPORT __attribute__((dllexport))
#            define XCAL_OPENGL_RENDERER_IMPORT __attribute__((dllimport))
#        else
// 使用MSVC或其他Windows编译器
#            define XCAL_OPENGL_RENDERER_EXPORT __declspec(dllexport)
#            define XCAL_OPENGL_RENDERER_IMPORT __declspec(dllimport)
#        endif
#    else
// 非Windows平台
#        if __GNUC__ >= 4
// 使用GCC 4及以上版本
#            define XCAL_OPENGL_RENDERER_EXPORT \
                __attribute__((visibility("default")))
#            define XCAL_OPENGL_RENDERER_IMPORT
#        else
// 其他编译器
#            define XCAL_OPENGL_RENDERER_EXPORT
#            define XCAL_OPENGL_RENDERER_IMPORT
#        endif
#    endif
#endif  // XCAL_ENABLE_DYNAMIC_LIBRARY

#ifdef XCAL_ENABLE_DYNAMIC_LIBRARY
#    ifdef XCAL_OPENGL_RENDERER_BUILD
#        define XCAL_OPENGL_RENDERER_API XCAL_OPENGL_RENDERER_EXPORT
#    else
#        define XCAL_OPENGL_RENDERER_API XCAL_OPENGL_RENDERER_IMPORT
#    endif
#else
#    define XCAL_OPENGL_RENDERER_API
#endif