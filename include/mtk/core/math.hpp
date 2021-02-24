#ifndef MTK_CORE_MATH_HPP
#define MTK_CORE_MATH_HPP

//! @file
//! Contains simple math functionality.

#include <mtk/core/assert.hpp>
#include <mtk/core/types.hpp>
#include <mtk/core/type_traits.hpp>

#include <limits>
#include <type_traits>

namespace mtk {

//! @defgroup math mtk/core/math.hpp
//! @{

//! Namespace for mathematical constants.
namespace math {

//! @addtogroup math
//! @{

//! @brief Approximation of π for the given type T.
//!
//! @pre T must be an arithmetic type.
template<class T
#ifndef MTK_DOXYGEN
	,require<std::is_arithmetic_v<T>> = 0
#endif
>
inline constexpr
T
pi = static_cast<T>(3.141592653589793238462643383279502884L);

//! @brief Approximation of Euler's constant for the given type T.
//!
//! @pre T must be an arithmetic type.
template<class T
#ifndef MTK_DOXYGEN
	,require<std::is_arithmetic_v<T>> = 0
#endif
>
inline constexpr
T
e = static_cast<T>(2.718281828459045235360287471352662498L);

//! @brief Approximation of the natural logarithm of 2
//! for the given type T.
//!
//! @pre T must be an arithmetic type.
template<class T
#ifndef MTK_DOXYGEN
	,require<std::is_arithmetic_v<T>> = 0
#endif
>
inline constexpr
T
ln_2 = static_cast<T>(0.693147180559945309417232121458176568L);

//! @brief Approximation of the natural logaritm of 10
//! for the given type T.
//!
//! @pre T must be an arithmetic type.
template<class T
#ifndef MTK_DOXYGEN
	,require<std::is_arithmetic_v<T>> = 0
#endif
>
inline constexpr
T
ln_10 = static_cast<T>(2.302585092994045684017991454684364208L);

//! @brief Approximation of the square root of 2
//! for the given type T.
//!
//! @pre T must be an arithmetic type.
template<class T
#ifndef MTK_DOXYGEN
	,require<std::is_arithmetic_v<T>> = 0
#endif
>
inline constexpr
T
sqrt_2 = static_cast<T>(1.414213562373095048801688724209698079L);

//! @brief Approximation of the square root of π
//! for the given type T.
//!
//! @pre T must be an arithmetic type.
template<class T
#ifndef MTK_DOXYGEN
	,require<std::is_arithmetic_v<T>> = 0
#endif
>
inline constexpr
T
sqrt_pi = static_cast<T>(2.0L / 1.128379167095512573896158903121545172L);

//! @}

} // namespace math



//! Returns the square of the given value.
template<class T>
constexpr
T
squared(T t) noexcept(noexcept(T(t*t)))
{
	return t*t;
}

//! Returns the cube of the given value.
template<class T>
constexpr
T
cubed(T t) noexcept(noexcept(T(t*t*t)))
{
	return t*t*t;
}



//! @brief Returns the sign of the given value (-1, 0, or 1).
//!
//! @pre T must be an arithmetic type.
template<class T
#ifndef MTK_DOXYGEN
	,require<std::is_arithmetic_v<T>> = 0
#endif
>
constexpr
T
sgn(T t) noexcept
{
	return T(int(T() < t) - int(t < T()));
}

//! @brief Returns the result of the heaviside step function of the given value (0, 1/2, 1 formalism).
//!
//! @pre T must be an arithmetic type.
template<class T
#ifndef MTK_DOXYGEN
	,require<std::is_arithmetic_v<T>> = 0
#endif
>
constexpr
T
heaviside(T t) noexcept
{
	return T((mtk::sgn(t) + T(1)) / T(2));
}



//! @brief Returns the factorial of the given value.
//!
//! @pre The given value must be non-negative.
float factorial(float);

//! @brief Returns the factorial of the given value.
//!
//! @pre The given value must be non-negative.
double factorial(double);

//! @brief Returns the factorial of the given value.
//!
//! @pre The given value must be non-negative.
ldouble factorial(ldouble);

//! @brief Returns the factorial of the given value.
//!
//! @pre T must be an integral type.
//! @pre The given value must be non-negative.
//!
//! @note This function has the given non-template overloads for floating point types:
//!  - float factorial(float);
//!  - double factorial(double);
//!  - ldouble factorial(ldouble);
template<class T
#ifndef MTK_DOXYGEN
	,require<std::is_integral_v<T>> = 0
#endif
>
real
factorial(T t)
{
	return factorial(static_cast<real>(t));
}



//! @brief Returns true if the given value is a power of 2,
//! else false.
//!
//! @pre T must be an integral type.
template<class T
#ifndef MTK_DOXYGEN
	,require<std::is_integral_v<T>> = 0
#endif
>
constexpr
bool
is_pow2(T t) noexcept
{
	//Not standard but works on any tangentially sensible implementation.
	static_assert(std::numeric_limits<T>::radix == 2);

	using ut = std::make_unsigned_t<T>;
	ut v = static_cast<ut>(t);

	return ( ((v & (v - ut(1))) == ut()) && (t > T()) );
}

//! @brief Returns the nearest power of 2 which
//! is greater than or equal to \p t.
//!
//! @pre T must be an integral type.
//! @pre The given value must be non-negative and
//! less than or equal to the highest representable power of 2.
template<class T
#ifndef MTK_DOXYGEN
	,require<std::is_integral_v<T>> = 0
#endif
	>
constexpr
T
next_pow2(T t) noexcept
{
	//Not standard but works on any tangentially sensible implementation.
	static_assert(std::numeric_limits<T>::radix == 2);
	MTK_PRECOND_LOW(t >= T());

	constexpr auto bits = std::numeric_limits<T>::digits;

	using u_t = std::make_unsigned_t<T>;
	u_t v = static_cast<u_t>(t);
	MTK_PRECOND_LOW(v <= (u_t(1) << (bits - 1)));

	--v;
	for (int i = 1; i < bits; i <<= 1) {
		v |= (v >> i);
	}
	++v;

	return static_cast<T>(t <= 0 ? u_t(1) : v);
}

//! @}

} // namespace mtk

#endif
