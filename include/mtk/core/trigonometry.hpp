#ifndef MTK_CORE_TRIGONOMETRY_HPP
#define MTK_CORE_TRIGONOMETRY_HPP

//! @file
//! Contains type-safe trigonometry

#include <mtk/core/assert.hpp>
#include <mtk/core/math.hpp>
#include <mtk/core/type_traits.hpp>

#include <utility>
#include <type_traits>

namespace mtk {

//! @defgroup trig mtk/core/trigonometry.hpp
//! @{

namespace impl_core {
template<class T
	,class Derived>
class angle_base
{ };

template<class T
	,class D>
constexpr
bool
operator==(const angle_base<T, D>& lhs, const angle_base<T, D>& rhs) noexcept
{
	return (static_cast<const D&>(lhs).value() == static_cast<const D&>(rhs).value());
}

template<class T
	,class D>
constexpr
bool
operator!=(const angle_base<T, D>& lhs, const angle_base<T, D>& rhs) noexcept
{
	return !(lhs == rhs);
}

template<class T
	,class D>
constexpr
bool
operator<(const angle_base<T, D>& lhs, const angle_base<T, D>& rhs) noexcept
{
	return (static_cast<const D&>(lhs).value() < static_cast<const D&>(rhs).value());
}

template<class T
	,class D>
constexpr
bool
operator>(const angle_base<T, D>& lhs, const angle_base<T, D>& rhs) noexcept
{
	return (rhs < lhs);
}

template<class T
	,class D>
constexpr
bool
operator<=(const angle_base<T, D>& lhs, const angle_base<T, D>& rhs) noexcept
{
	return !(rhs < lhs);
}

template<class T
	,class D>
constexpr
bool
operator>=(const angle_base<T, D>& lhs, const angle_base<T, D>& rhs) noexcept
{
	return !(lhs < rhs);
}

template<class T
	,class D>
constexpr
D
operator+(const angle_base<T, D>& rhs)
{
	return static_cast<const D&>(rhs);
}

template<class T
	,class D>
constexpr
D
operator-(const angle_base<T, D>& rhs)
{
	return D(-static_cast<const D&>(rhs).value());
}

template<class T
	,class D>
constexpr
D&
operator+=(angle_base<T, D>& lhs, const angle_base<T, D>& rhs) noexcept
{
	static_cast<D&>(lhs).value() += static_cast<const D&>(rhs).value();
	return static_cast<D&>(lhs);
}

template<class T
	,class D>
constexpr
D
operator+(const angle_base<T, D>& lhs, const angle_base<T, D>& rhs) noexcept
{
	D cp = static_cast<const D&>(lhs);
	cp += rhs;
	return cp;
}

template<class T
	,class D>
constexpr
D&
operator-=(angle_base<T, D>& lhs, const angle_base<T, D>& rhs) noexcept
{
	static_cast<D&>(lhs).value() -= static_cast<const D&>(rhs).value();
	return static_cast<D&>(lhs);
}

template<class T
	,class D>
constexpr
D
operator-(const angle_base<T, D>& lhs, const angle_base<T, D>& rhs) noexcept
{
	D cp = static_cast<const D&>(lhs);
	cp -= rhs;
	return cp;
}

template<class T
	,class D>
constexpr
D&
operator*=(angle_base<T, D>& lhs, typename D::value_type rhs) noexcept
{
	static_cast<D&>(lhs).value() *= rhs;
	return static_cast<D&>(lhs);
}

template<class T
	,class D>
constexpr
D
operator*(const angle_base<T, D>& lhs, typename D::value_type rhs) noexcept
{
	D cp = static_cast<const D&>(lhs);
	cp *= rhs;
	return cp;
}

template<class T
	,class D>
constexpr
D
operator*(typename D::value_type lhs, const angle_base<T, D>& rhs) noexcept
{
	return rhs * lhs;
}

template<class T
	,class D>
constexpr
D&
operator/=(angle_base<T, D>& lhs, typename D::value_type rhs) noexcept
{
	static_cast<D&>(lhs).value() /= rhs;
	return static_cast<D&>(lhs);
}

template<class T
	,class D>
constexpr
D
operator/(const angle_base<T, D>& lhs, typename D::value_type rhs) noexcept
{
	D cp = static_cast<const D&>(lhs);
	cp /= rhs;
	return cp;
}

template<class T
	,class D>
constexpr
T
operator/(const angle_base<T, D>& lhs, const angle_base<T, D>& rhs) noexcept
{
	return (static_cast<const D&>(lhs).value() / static_cast<const D&>(rhs).value());
}



template<class T
	,class = void>
struct is_angle_type : std::false_type { };

template<class T
	,class D>
struct is_angle_type<angle_base<T, D>, void> : std::false_type { };

template<class T>
struct is_angle_type<T
	,std::void_t<
		require<std::is_base_of_v<angle_base<typename T::value_type, T>, T>>
	>> : std::true_type { };

template<class To
	,class From>
constexpr
To
convert_angle(From angle) noexcept
{
	if constexpr (std::is_same_v<From, To>) {
		return angle;
	} else {
		constexpr auto fac = To::period / From::period;
		return To(angle.value()*fac);
	}
}



float sin(float val);
double sin(double val);
ldouble sin(ldouble val);
float cos(float val);
double cos(double val);
ldouble cos(ldouble val);
float tan(float val);
double tan(double val);
ldouble tan(ldouble val);

std::pair<float, float> sincos(float val);
std::pair<double, double> sincos(double val);
std::pair<ldouble, ldouble> sincos(ldouble val);

float asin(float val);
double asin(double val);
ldouble asin(ldouble val);
float acos(float val);
double acos(double val);
ldouble acos(ldouble val);
float atan(float val);
double atan(double val);
ldouble atan(ldouble val);
float atan2(float y, float x);
double atan2(double y, double x);
ldouble atan2(ldouble y, ldouble x);

} // namespace impl_core



//! @brief Class representing angle in radians.
//!
//! @pre T must be a floating point type.
//!
//! Supports the operators:
//!	 - bool operator==(radians, radians)
//!  - bool operator!=(radians, radians)
//!  - bool operator<(radians, radians)
//!  - bool operator>(radians, radians)
//!  - bool operator<=(radians, radians)
//!  - bool operator>=(radians, radians)
//!  - radians operator+(radians)
//!  - radians operator-(radians)
//!  - radians& operator+=(radians&, radians)
//!  - radians& operator-=(radians&, radians)
//!  - radians operator+(radians, radians)
//!  - radians operator-(radians, radians)
//!  - radians& operator*=(radians&, T)
//!  - radians& operator/=(radians&, T)
//!  - radians operator*(radians, T)
//!  - radians operator*(T, radians)
//!  - radians operator/(radians, T)
//!  - T operator/(radians, radians)
template<class T>
class radians
#ifndef MTK_DOXYGEN
	: public impl_core::angle_base<T, radians<T>>
#endif
{
	static_assert(std::is_floating_point_v<T>);
public:
	//! Typedef.
	using value_type = T;

	//! The primary branch cut.
	static constexpr
	T
	period = T(2)*math::pi<T>;

	//! Initializes to zero.
	constexpr
	radians() noexcept :
		m_value()
	{ }

	//! Initializes to value radians.
	explicit constexpr
	radians(T value) noexcept :
		m_value(value)
	{ }

	//! Returns the current value.
	explicit constexpr
	operator T() const noexcept { return m_value; }

	//! Returns the current value.
	constexpr
	const T&
	value() const noexcept { return m_value; }

	//! Returns the current value.
	constexpr
	T&
	value() noexcept { return m_value; }

private:
	T m_value;
};

//! @brief Class representing angle in degrees.
//!
//! @pre T must be a floating point type.
//!
//! Supports the operators:
//!	 - bool operator==(degrees, degrees)
//!  - bool operator!=(degrees, degrees)
//!  - bool operator<(degrees, degrees)
//!  - bool operator>(degrees, degrees)
//!  - bool operator<=(degrees, degrees)
//!  - bool operator>=(degrees, degrees)
//!  - degrees operator+(degrees)
//!  - degrees operator-(degrees)
//!  - degrees& operator+=(degrees&, degrees)
//!  - degrees& operator-=(degrees&, degrees)
//!  - degrees operator+(degrees, degrees)
//!  - degrees operator-(degrees, degrees)
//!  - degrees& operator*=(degrees&, T)
//!  - degrees& operator/=(degrees&, T)
//!  - degrees operator*(degrees, T)
//!  - degrees operator*(T, degrees)
//!  - degrees operator/(degrees, T)
//!  - T operator(degrees, degrees)
template<class T>
class degrees
#ifndef MTK_DOXYGEN
	: public impl_core::angle_base<T, degrees<T>>
#endif
{
	static_assert(std::is_floating_point_v<T>);
public:
	//! Typedef.
	using value_type = T;

	//! The primary branch cut.
	static constexpr
	T
	period = T(360);

	//! Initializes to zero.
	constexpr
	degrees() noexcept :
		m_value()
	{ }

	//! Initializes to value degrees.
	explicit constexpr
	degrees(T value) noexcept :
		m_value(value)
	{ }

	//! Returns the current value.
	explicit constexpr
	operator T() const noexcept { return m_value; }

	//! Returns the current value.
	constexpr
	const T&
	value() const noexcept { return m_value; }

	//! Returns the current value.
	constexpr
	T&
	value() noexcept { return m_value; }

private:
	T m_value;
};

//! @brief Deduction guide.
//! @relates radians
template<class T>
radians(T) -> radians<make_real_t<T>>;

//! @brief Deduction guide.
//! @relates degrees
template<class T>
degrees(T) -> degrees<make_real_t<T>>;



//! @brief Converts angle to radians.
//!
//! @pre T must be an angle type.
template<class T
#ifndef MTK_DOXYGEN
	,require<impl_core::is_angle_type<T>::value> = 0
#endif
>
radians<typename T::value_type>
to_radians(T angle)
{
	return mtk::impl_core::convert_angle<radians<typename T::value_type>>(angle);
}

//! @brief Converts angle to degrees.
//!
//! @pre T must be an angle type.
template<class T
#ifndef MTK_DOXYGEN
	,require<impl_core::is_angle_type<T>::value> = 0
#endif
>
degrees<typename T::value_type>
to_degrees(T angle)
{
	return mtk::impl_core::convert_angle<degrees<typename T::value_type>>(angle);
}



//! @brief Returns the sine of angle.
//!
//! @pre T must be an angle type.
template<class T
#ifndef MTK_DOXYGEN
	,require<mtk::impl_core::is_angle_type<T>::value> = 0
#endif
>
typename T::value_type
sin(T angle)
{
	return mtk::impl_core::sin(mtk::to_radians(angle).value());
}

//! @brief Returns the cosine of angle.
//!
//! @pre T must be an angle type.
template<class T
#ifndef MTK_DOXYGEN
	,require<mtk::impl_core::is_angle_type<T>::value> = 0
#endif
>
typename T::value_type
cos(T angle)
{
	return mtk::impl_core::cos(mtk::to_radians(angle).value());
}

//! @brief Returns the tangent of angle.
//!
//! @pre T must be an angle type.
template<class T
#ifndef MTK_DOXYGEN
	,require<mtk::impl_core::is_angle_type<T>::value> = 0
#endif
>
typename T::value_type
tan(T angle)
{
	return mtk::impl_core::tan(mtk::to_radians(angle).value());
}

//! @brief Returns the cosecant of angle.
//!
//! @pre T must be an angle type.
template<class T
#ifndef MTK_DOXYGEN
	,require<mtk::impl_core::is_angle_type<T>::value> = 0
#endif
>
typename T::value_type
csc(T angle)
{
	return typename T::value_type(1) / mtk::sin(angle);
}

//! @brief Returns the secant of angle.
//!
//! @pre T must be an angle type.
template<class T
#ifndef MTK_DOXYGEN
	,require<mtk::impl_core::is_angle_type<T>::value> = 0
#endif
>
typename T::value_type
sec(T angle)
{
	return typename T::value_type(1) / mtk::cos(angle);
}

//! @brief Returns the cotangent of angle.
//!
//! @pre T must be an angle type.
template<class T
#ifndef MTK_DOXYGEN
	,require<mtk::impl_core::is_angle_type<T>::value> = 0
#endif
>
typename T::value_type
cot(T angle)
{
	return typename T::value_type(1) / mtk::tan(angle);
}

//! @brief Returns the sine and cosine of angle.
//!
//! The first value returned is the sine,
//! the second is the cosine.
//!
//! @pre T must be an angle type.
template<class T
#ifndef MTK_DOXYGEN
	,require<mtk::impl_core::is_angle_type<T>::value> = 0
#endif
>
std::pair<typename T::value_type, typename T::value_type>
sincos(T angle)
{
	return mtk::impl_core::sincos(mtk::to_radians(angle).value());
}




//! @brief Returns the arcsine of value.
//!
//! @pre T must be an arithmetic type.
//! @pre value must be in [-1, 1].
template<class T>
radians<make_real_t<T>>
asin(T value)
{
	if constexpr (std::is_signed_v<T>)
		MTK_IMPL_LIB_ASSERT(value >= T(-1));
	MTK_IMPL_LIB_ASSERT(value <= T(1));
	return radians<make_real_t<T>>(mtk::impl_core::asin(value));
}

//! @brief Returns the arccosine of value.
//!
//! @pre T must be an arithmetic type.
//! @pre value must be in [-1, 1].
template<class T>
radians<make_real_t<T>>
acos(T value)
{
	if constexpr (std::is_signed_v<T>)
		MTK_IMPL_LIB_ASSERT(value >= T(-1));
	MTK_IMPL_LIB_ASSERT(value <= T(1));
	return radians<make_real_t<T>>(mtk::impl_core::acos(value));
}

//! @brief Returns the arctangent of value.
//!
//! @pre T must be an arithmetic type.
template<class T>
radians<make_real_t<T>>
atan(T value)
{
	return radians<make_real_t<T>>(mtk::impl_core::atan(value));
}

//! @brief Returns the arctangent of y/x using the signs to
//! determine the correct quadrant.
//!
//! @pre T must be an arithmetic type.
template<class T>
radians<make_real_t<T>>
atan2(T y, T x)
{
	return radians<make_real_t<T>>(mtk::impl_core::atan2(y, x));
}

//! @brief Returns the arccosecant of value.
//!
//! @pre T must be an arithmetic type.
//! @pre value must be in [1, inf) or [-1, -inf).
template<class T>
radians<make_real_t<T>>
acsc(T value)
{
	return mtk::asin(T(1) / value);
}

//! @brief Returns the arcsecant of value.
//!
//! @pre T must be an arithmetic type.
//! @pre value must be in [1, inf) or [-1, -inf).
template<class T>
radians<make_real_t<T>>
asec(T value)
{
	return mtk::acos(T(1) / value);
}

//! @brief Returns the arccotangent of value.
//!
//! @pre T must be an arithmetic type.
template<class T>
radians<make_real_t<T>>
acot(T value)
{
    return mtk::atan(T(1) / value);
}

//! @}

} // namespace mtk

#endif
