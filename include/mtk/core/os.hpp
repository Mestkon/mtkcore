#ifndef MTK_CORE_OS_HPP
#define MTK_CORE_OS_HPP

//! @file
//! Defines macros to check the target OS

//! @defgroup os mtk/core/os.hpp
//! @{

//! @ref MTK_OS is defined to this value if the target is windows.
#define MTK_OS_WINDOWS 0
//! @ref MTK_OS is defined to this value if the target is linux.
#define MTK_OS_LINUX 1
//! @ref MTK_OS is defined to this value if the target is macOS.
#define MTK_OS_MACOS 2
//! @ref MTK_OS is defined to this value if the target is android.
#define MTK_OS_ANDROID 3
//! @ref MTK_OS is defined to this value if the target is iOS.
#define MTK_OS_IOS 4
//! @ref MTK_OS is defined to this value if the target is BSD.
#define MTK_OS_BSD 5
//! @ref MTK_OS is defined to this value if the target is Solaris.
#define MTK_OS_SOLARIS 6
//! @ref MTK_OS is defined to this value if the target was unable to be detected.
#define MTK_OS_UNKNOWN 100

#ifdef MTK_DOXYGEN
//! @brief This is defined to one of the MTK_OS_* based on which OS is the compilation target.
//!
//! Can be overridden by defining it globally to one of the MTK_OS_* macros.
#define MTK_OS
#endif

#ifndef MTK_OS
	#if defined(_WIN32)
		#define MTK_OS MTK_OS_WINDOWS
	#elif defined(__CYGWIN__)
		#define MTK_OS MTK_OS_WINDOWS
	#elif defined(__ANDROID__)
		#define MTK_OS MTK_OS_ANDROID
	#elif defined(__linux)
		#define MTK_OS MTK_OS_LINUX
	#elif defined(__unix__) || !defined(__APPLE__) && defined(__MACH__)
		#include <sys/param.h>
		#if defined(BSD)
			#define MTK_OS MTK_OS_BSD
		#else
			#define MTK_OS MTK_OS_UNKNOWN
		#endif
	#elif defined(__APPLE__) && defined(__MACH__)
		#include <TargetConditionals.h>
		#if TARGET_IPHONE_SIMULATOR == 1
			#define MTK_OS MTK_OS_IOS
		#elif TARGET_OS_IPHONE == 1
			#define MTK_OS MTK_OS_IOS
		#elif TARGET_OS_MAC == 1
			#define MTK_OS MTK_OS_MACOS
		#else
			#define MTK_OS MTK_OS_UNKNOWN
		#endif
	#elif defined(__sun) && defined(__SVR4)
		#define MTK_OS MTK_OS_SOLARIS
	#else
		#define MTK_OS MTK_OS_UNKNOWN
	#endif
#endif

//! @}

#endif
