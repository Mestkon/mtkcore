#ifndef MTK_CORE_SCOPE_GUARD_HPP
#define MTK_CORE_SCOPE_GUARD_HPP

//! @file
//! Contains scope_guard, scope_success, and scope_failure.

#include <mtk/core/types.hpp>

#include <type_traits>

namespace mtk {

//! @defgroup scope mtk/core/scope_guard.hpp
//! @{

namespace impl_core {

int
uncaught_exceptions() noexcept;

} // namespace impl_core

//! @brief Invokes the given function when destroyed.
//!
//! Makes writing exception-safe code easier.
//! Works well with CTAD.
//!
//! @pre Func must be invokable.
template<class Func
#ifndef MTK_DOXYGEN
	,require<std::is_invocable_v<Func>> = 0
#endif
>
class scope_guard
{
public:
	//! Initializes the scope_guard with the given function.
	constexpr
	scope_guard(Func f) :
		m_func(static_cast<Func&&>(f))
		,m_active(true)
	{ }

	//! Deleted.
	scope_guard(const scope_guard&) = delete;

	//! Invokes the contained function unless release has been called.
	~scope_guard() noexcept
	{
		if (m_active)
			m_func();
	}

	//! Deleted.
	void
	operator=(const scope_guard&) = delete;

	//! Disables the scope_guard. Cannot be undone.
	constexpr
	void
	release() noexcept
	{
		m_active = false;
	}

private:
	Func m_func;
	bool m_active;
};

//! @brief Invokes the given function when destroyed if no
//! exceptions are currently uncaught.
//!
//! Makes writing exception-safe code easier.
//! Works well with CTAD.
//!
//! @pre Func must be invokable.
template<class Func
#ifndef MTK_DOXYGEN
	,require<std::is_invocable_v<Func>> = 0
#endif
>
class scope_success
{
public:
	//! Initializes the scope_success with the given function.
	constexpr
	scope_success(Func f) :
		m_func(static_cast<Func&&>(f))
		,m_active(true)
	{ }

	//! Deleted.
	scope_success(const scope_success&) = delete;

	//! Invokes the contained function unless there is uncaught exceptions or release has been called.
	~scope_success() noexcept
	{
		const bool has_exceptions = (mtk::impl_core::uncaught_exceptions() > 0);
		if (m_active && !has_exceptions)
			m_func();
	}

	//! Deleted.
	void
	operator=(const scope_success&) = delete;

	//! Disables the scope_success. Cannot be undone.
	constexpr
	void
	release() noexcept
	{
		m_active = false;
	}

private:
	Func m_func;
	bool m_active;
};

//! @brief Invokes the given function when destroyed if any
//! exceptions are currently uncaught.
//!
//! Makes writing exception-safe code easier.
//! Works well with CTAD.
//!
//! @pre Func must be invokable.
template<class Func
#ifndef MTK_DOXYGEN
	,require<std::is_invocable_v<Func>> = 0
#endif
>
class scope_failure
{
public:
	//! Initializes the scope_failure with the given function.
	constexpr
	scope_failure(Func f) :
		m_func(static_cast<Func&&>(f))
		,m_active(true)
	{ }

	//! Deleted.
	scope_failure(const scope_failure&) = delete;

	//! Invokes the contained function if there is uncaught exceptions or release has not been called.
	~scope_failure() noexcept
	{
		const bool has_exceptions = (mtk::impl_core::uncaught_exceptions() > 0);
		if (m_active && has_exceptions)
			m_func();
	}

	//! Deleted.
	void
	operator=(const scope_failure&) = delete;

	//! Disables the scope_failure. Cannot be undone.
	constexpr
	void
	release() noexcept
	{
		m_active = false;
	}

private:
	Func m_func;
	bool m_active;
};

//! @}

} // namespace mtk

#endif
