#ifndef TPLIB_COMMON_HH
#define TPLIB_COMMON_HH

#if defined(_WIN32) || defined(__WIN64)
#   define TPLIB_OS_WINDOWS
#else
#   define TPLIB_OS_UNIX
#endif

#ifdef TPLIB_OS_WINDOWS
#	define tplib_export __declspec(dllexport)
#else
#	define tplib_export /* sane */
#endif

namespace tplib {
}

#endif
