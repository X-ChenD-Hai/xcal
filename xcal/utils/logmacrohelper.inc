#pragma once
#if defined(LABEL) && defined(ROLE)
#define _I(msg)                        \
    do {                               \
        XCAL_INFO(ROLE, LABEL) << msg; \
        OUT(msg);                      \
    } while (1)
#define _W(msg)                        \
    do {                               \
        XCAL_WARN(ROLE, LABEL) << msg; \
        OUT(msg);                      \
    } while (1)
#define _E(msg)                         \
    do {                                \
        XCAL_ERROR(ROLE, LABEL) << msg; \
        OUT(msg);                       \
    } while (1)
#define _D(msg)                         \
    do {                                \
        XCAL_DEBUG(ROLE, LABEL) << msg; \
        OUT(msg);                       \
    } while (1)
#define _F(msg)                         \
    do {                                \
        XCAL_FATAL(ROLE, LABEL) << msg; \
        OUT(msg);                       \
    } while (1)
#elif defined(LABEL)
#define _I(role, msg)                  \
    do {                               \
        XCAL_INFO(role, LABEL) << msg; \
        OUT(msg);                      \
    } while (1)
#define _W(role, msg)                  \
    do {                               \
        XCAL_WARN(role, LABEL) << msg; \
        OUT(msg);                      \
    } while (1)
#define _E(role, msg)                   \
    do {                                \
        XCAL_ERROR(role, LABEL) << msg; \
        OUT(msg);                       \
    } while (1)
#define _D(role, msg)                   \
    do {                                \
        XCAL_DEBUG(role, LABEL) << msg; \
        OUT(msg);                       \
    } while (1)
#define _F(role, msg)                   \
    do {                                \
        XCAL_FATAL(role, LABEL) << msg; \
        OUT(msg);                       \
    } while (1)
#elif defined(ROLE)
#define _I(label, msg)                 \
    do {                               \
        XCAL_INFO(ROLE, label) << msg; \
        OUT(msg);                      \
    } while (1)
#define _W(label, msg)                 \
    do {                               \
        XCAL_WARN(ROLE, label) << msg; \
        OUT(msg);                      \
    } while (1)
#define _E(label, msg)                  \
    do {                                \
        XCAL_ERROR(ROLE, label) << msg; \
        OUT(msg);                       \
    } while (1)
#define _D(label, msg)                  \
    do {                                \
        XCAL_DEBUG(ROLE, label) << msg; \
        OUT(msg);                       \
    } while (1)
#define _F(label, msg)                  \
    do {                                \
        XCAL_FATAL(ROLE, label) << msg; \
        OUT(msg);                       \
    } while (1)
#else
#define _I(role, label, msg)           \
    do {                               \
        XCAL_INFO(role, label) << msg; \
        OUT(msg);                      \
    } while (1)
#define _W(role, label, msg)           \
    do {                               \
        XCAL_WARN(role, label) << msg; \
        OUT(msg);                      \
    } while (1)
#define _E(role, label, msg)            \
    do {                                \
        XCAL_ERROR(role, label) << msg; \
        OUT(msg);                       \
    } while (1)
#define _D(role, label, msg)            \
    do {                                \
        XCAL_DEBUG(role, label) << msg; \
        OUT(msg);                       \
    } while (1)
#define _F(role, label, msg)            \
    do {                                \
        XCAL_FATAL(role, label) << msg; \
        OUT(msg);                       \
    } while (1)
#endif

#ifdef XCAL_STATIC_LOG_LEVEL
#if XCAL_DEBUG_LEVEL <= XCAL_STATIC_LOG_LEVEL
#undef _D
#define _D(...)
#endif
#if XCAL_INFO_LEVEL <= XCAL_STATIC_LOG_LEVEL
#undef _I
#define _I(...)
#endif
#if XCAL_WARN_LEVEL <= XCAL_STATIC_LOG_LEVEL
#undef _W
#define _W(...)
#endif
#if XCAL_ERROR_LEVEL <= XCAL_STATIC_LOG_LEVEL
#undef _E
#define _E(...)
#endif
#if XCAL_FATAL_LEVEL <= XCAL_STATIC_LOG_LEVEL
#undef _F
#define _F(...)
#endif
#endif

#define _NAMED_VALUE(value)                \
    << "(" << #value << "=" << name << " " \
    << ")"
#define _LINE_MSG(msg) \
    do {               \
    << msg << "\n"
#define _SELF << "(" << this << ")"
#ifdef XCAL_OUT_TO_STDERR
constexpr static auto PRO_LEN =
    sizeof("D:\\31003\\Desktop\\code\\C++\\xc1\\xcal");
#define OUT(msg)                                                     \
    std::cerr << "[" << _STD string(__FILE__).substr(PRO_LEN) << ":" \
              << __LINE__ << "] " << msg << std::endl;
#else
#define OUT(msg) \
    do {         \
    } while (0)
#endif