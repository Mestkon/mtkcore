#ifndef MTK_CORE_ASSERT_HPP
#define MTK_CORE_ASSERT_HPP

//! @file
//! Contains assertion macros.

namespace mtk {

//! @defgroup assert mtk/core/assert.hpp
//! @{

#ifdef MTK_DOXYGEN
	//! Define project-wide in debug builds.
	#define MTK_DEBUG

	//! @brief Define project-wide to disable library internal asserts in debug mode.
	//!
	//! Useful if the code runs too slow in debug mode.
	#define MTK_NO_LIB_ASSERTS
#endif

namespace impl_core {

[[noreturn]]
void
assertion_handler(const char* what, const char* file, int line) noexcept;

} // namespace impl_core

#define MTK_IMPL_LIVE_ASSERT(...) static_cast<void>(!static_cast<bool>(__VA_ARGS__) && (mtk::impl_core::assertion_handler(#__VA_ARGS__, __FILE__, __LINE__), 1))
#define MTK_IMPL_DUD_ASSERT(...) static_cast<void>(0)

#ifdef MTK_DEBUG
	#define MTK_IMPL_ASSERT(...) MTK_IMPL_LIVE_ASSERT(__VA_ARGS__)
#else
	#define MTK_IMPL_ASSERT(...) MTK_IMPL_DUD_ASSERT(__VA_ARGS__)
#endif

#if defined(MTK_DEBUG) && !defined(MTK_NO_LIB_ASSERTS)
	#define MTK_IMPL_LIB_ASSERT(...) MTK_IMPL_LIVE_ASSERT(__VA_ARGS__)
#else
	#define MTK_IMPL_LIB_ASSERT(...) MTK_IMPL_DUD_ASSERT(__VA_ARGS__)
#endif



//! @brief Asserts the given boolean expression.
//!
//! Calls std::terminate if MTK_DEBUG is defined and the provided
//! boolean expression evaluates to false. The expression will not be
//! evaluated if MTK_DEBUG is not defined.
//!
//! @pre The given expression must be explicitly convertible to bool.
#define MTK_ASSERT(...) MTK_IMPL_ASSERT(__VA_ARGS__)

//! \}

} // namespace mtk

#endif
