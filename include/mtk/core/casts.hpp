#ifndef MTK_CORE_CASTS_HPP
#define MTK_CORE_CASTS_HPP

//! @file
//! Contains c++-like casting functions.

#include <mtk/core/assert.hpp>
#include <mtk/core/type_traits.hpp>

#include <limits>
#include <type_traits>

namespace mtk {

//! @defgroup casts mtk/core/casts.hpp
//! @{

#ifdef MTK_DOXYGEN
	//! @brief Define project-wide to include everything in mtk::casts
	//! into the global namespace.
	#define MTK_GLOBAL_CASTS
#endif

namespace impl_core {

template<class Func>
struct const_function { };

template<class R
	,class... Args>
struct const_function<R(Args...)>
{
	using type = R(Args...) const;
};

} // namespace impl_core

//! Inline namespace for cast-like functions.
inline namespace casts {

//! @addtogroup casts
//! @{

//! @brief Converts the given cv-qualified pointer to T
//! to a corresponding cv-qualified pointer to mtk::byte.
//!
//! @pre T is trivially copyable or void.
template<class T
#ifndef MTK_DOXYGEN
	,require<std::is_trivially_copyable_v<std::remove_cv_t<T>> ||
		std::is_void_v<std::remove_cv_t<T>>> = 0
#endif
>
copy_cv_t<byte, T>*
byte_cast(T* t) noexcept
{
	return reinterpret_cast<copy_cv_t<byte, T>*>(t);
}



//! @brief Converts the given value to U, clamping it to the
//! domain of U.
//!
//! @pre T and U must be arithmetic types.
template<class U
	,class T
#ifndef MTK_DOXYGEN
	,require<std::is_arithmetic_v<T>> = 0
	,require<std::is_arithmetic_v<U>> = 0
#endif
>
constexpr
U
saturate_cast(T t) noexcept
{
	constexpr T t_min = std::numeric_limits<T>::lowest();
	constexpr T t_max = std::numeric_limits<T>::max();
	constexpr U u_min = std::numeric_limits<U>::lowest();
	constexpr U u_max = std::numeric_limits<U>::max();

	constexpr ldouble t_min_wide = static_cast<ldouble>(t_min);
	constexpr ldouble t_max_wide = static_cast<ldouble>(t_max);
	constexpr ldouble u_min_wide = static_cast<ldouble>(u_min);
	constexpr ldouble u_max_wide = static_cast<ldouble>(u_max);

	constexpr bool t_has_nan = std::numeric_limits<T>::has_quiet_NaN
		|| std::numeric_limits<T>::has_signaling_NaN;
	constexpr bool u_has_nan = std::numeric_limits<U>::has_quiet_NaN
		|| std::numeric_limits<U>::has_signaling_NaN;

	if constexpr (t_has_nan && !u_has_nan) {
		if (t != t) {
			return U();
		}
	}

	constexpr bool t_in_domain_of_u = (t_min_wide >= u_min_wide) && (t_max_wide <= u_max_wide);
	constexpr bool infinity_compatible = (std::numeric_limits<T>::has_infinity && std::numeric_limits<U>::has_infinity) ||
		!std::numeric_limits<T>::has_infinity;

	if constexpr (t_in_domain_of_u && infinity_compatible) {
		return static_cast<U>(t);
	} else {
		constexpr T min = (t_min_wide < u_min_wide ? static_cast<T>(u_min) : t_min);
		constexpr T max = (t_max_wide > u_max_wide ? static_cast<T>(u_max) : t_max);

		return static_cast<U>(t < min ? min : (t > max ? max : t));
	}
}

//! @brief Converts the given value to U. Asserts that
//! no precision has been lost if MTK_DEBUG is defined.
//!
//! @pre T and U must be arithmetic types.
template<class U
	,class T
#ifndef MTK_DOXYGEN
	,require<std::is_arithmetic_v<T>> = 0
	,require<std::is_arithmetic_v<U>> = 0
#endif
>
constexpr
U
narrow_cast(T t) noexcept
{
#ifdef MTK_DEBUG
	constexpr bool t_has_nan = std::numeric_limits<T>::has_quiet_NaN
		|| std::numeric_limits<T>::has_signaling_NaN;
	constexpr bool u_has_nan = std::numeric_limits<U>::has_quiet_NaN
		|| std::numeric_limits<U>::has_signaling_NaN;

	if constexpr (t_has_nan && u_has_nan)
		MTK_ASSERT((static_cast<T>(mtk::saturate_cast<U>(t)) == t) || (t != t));
	else
		MTK_ASSERT(static_cast<T>(mtk::saturate_cast<U>(t)) == t);
#endif

	return static_cast<U>(t);
}



//! @brief Selects the free/member function overload corresponding to the given function signature.
//!
//! The const qualifier is optional if the given overload does not have
//! a non-const overload.
//!
//! @pre Func must be a function signature.
//!
//! @code
//! void f();
//! int f(int);
//! float f(bool);
//!
//! auto ptr = mtk::overload_cast<int(int)>(&f)
//! //type of ptr is int(*)(int)
//!
//! struct S {
//!  void f();
//!  int f(int) const;
//!  float f(bool);
//!  float f(bool) const;
//! };
//!
//! auto ptr1 = mtk::overload_cast<float(bool)>(&S::f);
//! //type of ptr1 is float(S::*)(bool)
//! auto ptr2 = mtk::overload_cast<float(bool) const>(&S::f);
//! //type of ptr2 is float(S::*)(bool) const
//! auto ptr3 = mtk::overload_cast<int(int)>(&S::f);
//! //type of ptr3 is int(S::*)(int) const
//! @endcode
template<class Func
#ifndef MTK_DOXYGEN
	,require<std::is_function_v<Func>> = 0
#endif
>
constexpr
auto
overload_cast(Func* ptr) noexcept { return ptr; }

template<class Func
	,class T
	,require<std::is_function_v<Func>> = 0>
constexpr
auto
overload_cast(Func T::*&& ptr) noexcept { return ptr; }

template<class Func
	,class T
	,require<std::is_function_v<Func>> = 0>
constexpr
auto
overload_cast(typename impl_core::const_function<Func>::type T::* const & ptr) noexcept { return ptr; }

//! @}

} // namespace casts



//! @brief Returns the address of the given object. Equivalent to std::addressof.
//!
//! An alternative to std::addressof if one consider <memory> too large for
//! only std::addressof.
template<class T>
T*
addressof(T& ref) noexcept
{
	using byte_type = copy_cv_t<byte, T>;
	return reinterpret_cast<T*>(&reinterpret_cast<byte_type&>(ref));
}

//! @}

} // namespace mtk

#ifdef MTK_GLOBAL_CASTS
	using namespace mtk::casts;
#endif


#endif
