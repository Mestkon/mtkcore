#ifndef MTK_CORE_TRIGONOMETRY_HPP
#define MTK_CORE_TRIGONOMETRY_HPP

//! @file
//! Contains type-safe trigonometry

#include <mtk/core/assert.hpp>
#include <mtk/core/math.hpp>
#include <mtk/core/type_traits.hpp>

#include <cmath>

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



//! Converts degrees to radians.
template<class T>
constexpr
radians<T>
to_radians(degrees<T> degs) noexcept
{
	constexpr T fac = math::pi<T> / T(180);
	return radians<T>{degs.value()*fac};
}

//! Converts radians to degrees.
template<class T>
constexpr
degrees<T>
to_degrees(radians<T> rads) noexcept
{
	constexpr T fac = T(180) / math::pi<T>;
	return degrees<T>{rads.value()*fac};
}



//! Returns the sine of rads.
template<class T>
T
sin(radians<T> rads)
{
	return std::sin(rads.value());
}

//! Returns the sine of degs.
template<class T>
T
sin(degrees<T> degs)
{
	return mtk::sin(mtk::to_radians(degs));
}

//! Returns the cosine of rads.
template<class T>
T
cos(radians<T> rads)
{
	return std::cos(rads.value());
}

//! Returns the cosine of degs.
template<class T>
T
cos(degrees<T> degs)
{
	return mtk::cos(mtk::to_radians(degs));
}

//! Returns the tangent of rads.
template<class T>
T
tan(radians<T> rads)
{
	return std::tan(rads.value());
}

//! Returns the tangent of degs.
template<class T>
T
tan(degrees<T> degs)
{
	return mtk::tan(mtk::to_radians(degs));
}

//! Returns the cosecant of rads.
template<class T>
T
csc(radians<T> rads)
{
	return T(1) / mtk::sin(rads);
}

//! Returns the cosecant of degs.
template<class T>
T
csc(degrees<T> degs)
{
	return mtk::csc(mtk::to_radians(degs));
}

//! Returns the secant of rads.
template<class T>
T
sec(radians<T> rads)
{
	return T(1) / mtk::cos(rads);
}

//! Returns the secant of degs.
template<class T>
T
sec(degrees<T> degs)
{
	return mtk::sec(mtk::to_radians(degs));
}

//! Returns the cotangent of rads.
template<class T>
T
cot(radians<T> rads)
{
	return T(1) / mtk::tan(rads);
}

//! Returns the cotangent of degs.
template<class T>
T
cot(degrees<T> degs)
{
	return mtk::cot(mtk::to_radians(degs));
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
	return radians<make_real_t<T>>(std::asin(value));
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
	return radians<make_real_t<T>>(std::acos(value));
}

//! @brief Returns the arctangent of value.
//!
//! @pre T must be an arithmetic type.
template<class T>
radians<make_real_t<T>>
atan(T value)
{
	return radians<make_real_t<T>>(std::atan(value));
}

//! @brief Returns the arctangent of y/x using the signs to
//! determine the correct quadrant.
//!
//! @pre T must be an arithmetic type.
template<class T>
radians<make_real_t<T>>
atan2(T y, T x)
{
	return radians<make_real_t<T>>(std::atan2(y, x));
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
        using U = make_real_t<T>;
        constexpr auto term = math::pi<U> / U(2);
        if (value == T())
			return radians<U>();
        else if (value > T())
			return (radians<U>(term) - mtk::atan(U(1) / value));
		else
			return (radians<U>(-term) - mtk::atan(U(1) / value));
}

//! @}

} // namespace mtk

#endif
