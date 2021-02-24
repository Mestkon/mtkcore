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

	//! @brief Define to select precondition check level.
	//!
	//! Can be defined to either MTK_PRECOND_NONE, MTK_PRECOND_LOW_COST, MTK_PRECOND_MED_COST,
	//! MTK_PRECOND_HI_COST, or MTK_PRECOND_ALL. Default is MTK_PRECOND_LEVEL_MED.
	//!
	//! Preconditions are only checked if MTK_DEBUG is defined.
	#define MTK_PRECOND_LEVEL
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



//! @brief Asserts the given boolean expression.
//!
//! Calls std::terminate if MTK_DEBUG is defined and the provided
//! boolean expression evaluates to false. The expression will not be
//! evaluated if MTK_DEBUG is not defined.
//!
//! @pre The given expression must be explicitly convertible to bool.
#define MTK_ASSERT(...) MTK_IMPL_ASSERT(__VA_ARGS__)



//! MTK_PRECOND_LEVEL is equal to this if precondition checks are disabled.
#define MTK_PRECOND_NONE 0
//! MTK_PRECOND_LEVEL is equal to this if only low cost preconditions are checked (O < function O).
#define MTK_PRECOND_LOW_COST 1
//! MTK_PRECOND_LEVEL is equal to this if low or medium cost preconditions are checked  (O <= function).
#define MTK_PRECOND_MED_COST 2
//! MTK_PRECOND_LEVEL is equal to this if low, medium, and high cost preconditions are checked.
#define MTK_PRECOND_HI_COST 3
//! MTK_PRECOND_LEVEL is equal to this if all preconditions are checked (Same as MTK_PRECOND_HI_COST).
#define MTK_PRECOND_ALL MTK_PRECOND_HI_COST

#ifndef MTK_PRECOND_LEVEL
	#define MTK_PRECOND_LEVEL MTK_PRECOND_MED_COST
#endif

#if MTK_PRECOND_LEVEL >= MTK_PRECOND_LOW_COST
	#define MTK_PRECOND_LOW(...) MTK_ASSERT(__VA_ARGS__)
#else
	#define MTK_PRECOND_LOW(...) MTK_IMPL_DUD_ASSERT(__VA_ARGS__)
#endif

#if MTK_PRECOND_LEVEL >= MTK_PRECOND_MED_COST
	#define MTK_PRECOND_MED(...) MTK_ASSERT(__VA_ARGS__)
#else
	#define MTK_PRECOND_MED(...) MTK_IMPL_DUD_ASSERT(__VA_ARGS__)
#endif

#if MTK_PRECOND_LEVEL >= MTK_PRECOND_HI_COST
	#define MTK_PRECOND_HI(...) MTK_ASSERT(__VA_ARGS__)
#else
	#define MTK_PRECOND_HI(...) MTK_IMPL_DUD_ASSERT(__VA_ARGS__)
#endif

//! \}

} // namespace mtk

#endif
