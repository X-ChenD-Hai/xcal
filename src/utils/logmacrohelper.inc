#pragma once
#if defined(LABEL) && defined(ROLE)
#define _I(msg) XCAL_INFO(ROLE, LABEL) << msg
#define _W(msg) XCAL_WARN(ROLE, LABEL) << msg
#define _E(msg) XCAL_ERROR(role, LABEL) << msg
#define _D(msg) XCAL_DEBUG(role, LABEL) << msg
#define _F(msg) XCAL_FATAL(role, LABEL) << msg
#elif defined(LABEL)
#define _I(role, msg) XCAL_INFO(role, LABEL) << msg
#define _W(role, msg) XCAL_WARN(role, LABEL) << msg
#define _E(role, msg) XCAL_ERROR(role, LABEL) << msg
#define _D(role, msg) XCAL_DEBUG(role, LABEL) << msg
#define _F(role, msg) XCAL_FATAL(role, LABEL) << msg
#elif defined(ROLE)
#define _I(label, msg) XCAL_INFO(ROLE, label) << msg
#define _W(label, msg) XCAL_WARN(ROLE, label) << msg
#define _E(label, msg) XCAL_ERROR(ROLE, label) << msg
#define _D(label, msg) XCAL_DEBUG(ROLE, label) << msg
#define _F(label, msg) XCAL_FATAL(ROLE, label) << msg
#else
#define _I(role, label) XCAL_INFO(role, label) << msg
#define _W(role, label) XCAL_WARN(role, label) << msg
#define _E(role, label) XCAL_ERROR(role, label) << msg
#define _D(role, label) XCAL_DEBUG(role, label) << msg
#define _F(role, label) XCAL_FATAL(role, label) << msg
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

#define _NAMED_VALUE(value) << "(" << #value << "=" << name << " " << ")"
#define _LINE_MSG(msg) << msg << "\n"
#define _SELF << "(" << this << ")"