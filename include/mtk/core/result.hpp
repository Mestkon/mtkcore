#ifndef MTK_CORE_RESULT_HPP
#define MTK_CORE_RESULT_HPP

//! @file
//! Contains the result class template.

#include <mtk/core/assert.hpp>
#include <mtk/core/types.hpp>

#include <exception>
#include <type_traits>
#include <utility>
#include <variant>

namespace mtk {
namespace impl_core {
[[noreturn]]
void
throw_bad_result_access();
} // namespace impl_core

//! @defgroup result mtk/core/result.hpp
//! @{

//! @brief Thrown by result if dereferenced while in error state.
//!
//! @sa result
struct bad_result_access :
	public std::exception
{
	const char*
	what() const noexcept override;
};

//! @brief An <optional>-like class with room for an error type
//! when not engaged.
//!
//! Used to return an error state with the result of the function.
//!
//! @pre Error must be nothrow default constructible.
//! @pre Error must be copy constructible.
//! @pre Error must be copy assignable.
//! @pre Error must be destructible.
template<class T
	,class Error>
class result
{
	static_assert(std::is_nothrow_default_constructible_v<Error>);
	static_assert(std::is_copy_constructible_v<Error>);
	static_assert(std::is_copy_assignable_v<Error>);
	static_assert(std::is_destructible_v<Error>);
public:
	//!Initializes to a default constructed Error.
	result() noexcept :
		m_var()
	{ }

	//! Initializes to the given error state.
	result(Error err) noexcept(std::is_nothrow_move_constructible_v<Error>) :
		m_var(std::move(err))
	{ }

	//! @brief Initializes to the given value.
	//!
	//! @pre U must be convertible to T.
	template<class U
#ifndef MTK_DOXYGEN
		,require<std::is_convertible_v<U, T>> = 0
#endif
	>
	result(U&& value) noexcept(std::is_nothrow_constructible_v<T, U>) :
		m_var(static_cast<T>(std::forward<U>(value)))
	{ }

	//! @brief Returns true if the result contains a value.

	//! Returns false if the result contains an error.
	explicit
	operator bool() const noexcept { return (m_var.index() == 1); }

	//! Returns bool(*this)
	bool
	has_value() const noexcept { return bool(*this); }

	//! @brief Returns the current error state.
	//!
	//! @pre has_value() is false.
	Error
	error() const { MTK_IMPL_LIB_ASSERT(!*this); return std::get<0>(m_var); }



	//! @brief Returns a pointer to the current value.
	//!
	//! @pre has_value() is true.
	T*
	operator->() noexcept { MTK_IMPL_LIB_ASSERT(*this); return std::get_if<1>(&m_var); }

	//! @copydoc operator->()
	const T*
	operator->() const noexcept { MTK_IMPL_LIB_ASSERT(*this); return std::get_if<1>(&m_var); }

	//! @brief Returns a reference to the current value.
	//!
	//! @pre has_value() is true.
	T&
	operator*() & noexcept { return this->_value(); }

	//! @copydoc operator*()
	const T&
	operator*() const & noexcept { return this->_value(); }

	//! @copydoc operator*()
	T&&
	operator*() && noexcept { return std::move(this->_value); }

	//! @copydoc operator*()
	const T&&
	operator*() const && noexcept { return std::move(this->_value); }



	//! @brief Returns a reference to the given value.
	//!
	//! Throws bad_result_access if has_value() is false.
	T&
	value() & { return this->_safe_value(); }

	//! @copydoc value()
	const T&
	value() const & { return this->_safe_value(); }

	//! @copydoc value()
	T&&
	value() && { return std::move(this->_safe_value());  }

	//! @copydoc value()
	const T&&
	value() const && { return std::move(this->_safe_value()); }



	//! @brief Returns the current value if has_value() is true, else default_value.
	template<class U
#ifndef MTK_DOXYGEN
		,require<std::is_convertible_v<U, T>> = 0
#endif
	>
	T
	value_or(U&& default_value) const & { return bool(*this) ? **this : static_cast<T>(std::forward<U>(default_value)); }

	//! @copydoc value_or()
	template<class U
#ifndef MTK_DOXYGEN
		,require<std::is_convertible_v<U, T>> = 0
#endif
	>
	T
	value_or(U&& default_value) && { return bool(*this) ? std::move(**this) : static_cast<T>(std::forward<U>(default_value)); }

private:
	T& _value() { MTK_IMPL_LIB_ASSERT(*this); return std::get<1>(m_var); }
	const T& _value() const { MTK_IMPL_LIB_ASSERT(*this); return std::get<1>(m_var); }
	T& _safe_value() { if (!*this) impl_core::throw_bad_result_access(); return this->_value(); }
	const T& _safe_value() const { if (!*this) impl_core::throw_bad_result_access(); return this->_value(); }

	std::variant<Error, T> m_var;
};

//! @}

} // namespace mtk

#endif
