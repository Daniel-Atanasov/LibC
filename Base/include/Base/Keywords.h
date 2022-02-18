#pragma once

#define internal static
#define global   static
#define constant static const

#define cast(type, value) ((type)(value))

#define not !
#define and &&
#define or  ||

#define null cast(Pointer, 0)

#define true  cast(Bool, 1)
#define false cast(Bool, 0)

#ifdef offsetof
#undef offsetof
#endif

#define offsetof(type, member) cast(Uint64, &cast(type*, null)->member)

#ifdef NDEBUG
#define CONFIG_DEBUG false
#else
#define CONFIG_DEBUG true
#endif

#define debug   if (CONFIG_DEBUG)
#define release if (not CONFIG_DEBUG)

#ifndef __cplusplus
#define auto __auto_type
#endif