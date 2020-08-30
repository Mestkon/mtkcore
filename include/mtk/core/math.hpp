#ifndef MTK_CORE_MATH_HPP
#define MTK_CORE_MATH_HPP

//! @file
//! Contains simple math functionality.

#include <mtk/core/assert.hpp>
#include <mtk/core/types.hpp>
#include <mtk/core/type_traits.hpp>

#include <limits>

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
pi_value = static_cast<T>(3.141592653589793238462643383279502884L);

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
e_value = static_cast<T>(2.718281828459045235360287471352662498L);

//! Equivalent to mtk::math::pi_value<mtk::real>
inline constexpr
real
pi = pi_value<real>;

//! Equivalent to mtk::math::e_value<mtk::real>
inline constexpr
real
e = e_value<real>;

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



//! @brief Returns the given degree value as radians.
//!
//! @pre T must be an arithmetic type.
template<class T
#ifndef MTK_DOXYGEN
	,require<std::is_arithmetic_v<T>> = 0
#endif
>
make_real_t<T>
to_radians(T degrees) noexcept
{
	using U = make_real_t<T>;
	constexpr U fac = math::pi_value<U> / U(180);
	return fac*degrees;
}

//! @brief Returns the given radian value as degrees.
//!
//! @pre T must be an arithmetic type.
template<class T
#ifndef MTK_DOXYGEN
	,require<std::is_arithmetic_v<T>> = 0
#endif
>
make_real_t<T>
to_degrees(T radians) noexcept
{
	using U = make_real_t<T>;
	constexpr U fac = U(180) / math::pi_value<U>;
	return fac*radians;
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

//! @brief Returns the result of the heaviside step function (0, 1/2, 1 formalism).
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




float factorial(float);
double factorial(double);
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
	MTK_IMPL_LIB_ASSERT(t >= T());

	constexpr auto bits = std::numeric_limits<T>::digits;

	using u_t = std::make_unsigned_t<T>;
	u_t v = static_cast<u_t>(t);
	MTK_IMPL_LIB_ASSERT(v <= (u_t(1) << (bits - 1)));

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
