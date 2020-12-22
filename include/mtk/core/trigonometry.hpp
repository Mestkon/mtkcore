#ifndef MTK_CORE_TRIGONOMETRY_HPP
#define MTK_CORE_TRIGONOMETRY_HPP

#include <mtk/core/assert.hpp>
#include <mtk/core/math.hpp>
#include <mtk/core/type_traits.hpp>

#include <cmath>

namespace mtk {
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

} // namespace impl_core



template<class T>
class degrees
#ifndef MTK_DOXYGEN
	: public impl_core::angle_base<T, degrees<T>>
#endif
{
public:
	using value_type = T;

	constexpr
	degrees() noexcept :
		m_value()
	{ }

	explicit constexpr
	degrees(T value) noexcept :
		m_value(value)
	{ }

	explicit constexpr
	operator T() const noexcept { return m_value; }

	constexpr
	const T&
	value() const noexcept { return m_value; }

	constexpr
	T&
	value() noexcept { return m_value; }

private:
	T m_value;
};

template<class T>
class radians
#ifndef MTK_DOXYGEN
	: public impl_core::angle_base<T, radians<T>>
#endif
{
public:
	using value_type = T;

	constexpr
	radians() noexcept :
		m_value()
	{ }

	explicit constexpr
	radians(T value) noexcept :
		m_value(value)
	{ }

	explicit constexpr
	operator T() const noexcept { return m_value; }

	constexpr
	const T&
	value() const noexcept { return m_value; }

	constexpr
	T&
	value() noexcept { return m_value; }

private:
	T m_value;
};

template<class T>
degrees(T) -> degrees<make_real_t<T>>;

template<class T>
radians(T) -> radians<make_real_t<T>>;



template<class T>
constexpr
radians<T>
to_radians(degrees<T> degs) noexcept
{
	constexpr T fac = math::pi<T> / T(180);
	return radians<T>{degs.value()*fac};
}

template<class T>
constexpr
degrees<T>
to_degrees(radians<T> rads) noexcept
{
	constexpr T fac = T(180) / math::pi<T>;
	return degrees<T>{rads.value()*fac};
}



template<class T>
T
sin(radians<T> rads)
{
	return std::sin(rads.value());
}

template<class T>
T
sin(degrees<T> degs)
{
	return mtk::sin(mtk::to_radians(degs));
}

template<class T>
T
cos(radians<T> rads )
{
	return std::cos(rads.value());
}

template<class T>
T
cos(degrees<T> degs)
{
	return mtk::cos(mtk::to_radians(degs));
}

template<class T>
T
tan(radians<T> rads)
{
	return std::tan(rads.value());
}

template<class T>
T
tan(degrees<T> degs)
{
	return mtk::tan(mtk::to_radians(degs));
}

template<class T>
T
csc(radians<T> rads)
{
	return T(1) / mtk::sin(rads);
}

template<class T>
T
csc(degrees<T> degs)
{
	return mtk::csc(mtk::to_radians(degs));
}

template<class T>
T
sec(radians<T> rads)
{
	return T(1) / mtk::cos(rads);
}

template<class T>
T
sec(degrees<T> degs)
{
	return mtk::sec(mtk::to_radians(degs));
}

template<class T>
T
cot(radians<T> rads)
{
	return T(1) / mtk::tan(rads);
}

template<class T>
T
cot(degrees<T> degs)
{
	return mtk::cot(mtk::to_radians(degs));
}



template<class T>
radians<make_real_t<T>>
asin(T value)
{
	MTK_IMPL_LIB_ASSERT(value >= T());
	MTK_IMPL_LIB_ASSERT(value <= T(1));
	return radians<make_real_t<T>>(std::asin(value));
}

template<class T>
radians<make_real_t<T>>
acos(T value)
{
	MTK_IMPL_LIB_ASSERT(value >= T());
	MTK_IMPL_LIB_ASSERT(value <= T(1));
	return radians<make_real_t<T>>(std::acos(value));
}

template<class T>
radians<make_real_t<T>>
atan(T value)
{
	return radians<make_real_t<T>>(std::atan(value));
}

template<class T>
radians<make_real_t<T>>
atan2(T y, T x)
{
	return radians<make_real_t<T>>(std::atan2(y, x));
}

template<class T>
radians<make_real_t<T>>
acsc(T value)
{
	return mtk::asin(T(1) / value);
}

template<class T>
radians<make_real_t<T>>
asec(T value)
{
	return mtk::acos(T(1) / value);
}

template<class T>
radians<make_real_t<T>>
acot(T value)
{
        using U = make_real_t<T>;
        constexpr auto term = math::pi<U> / U(2);
        return (radians<U>(term) - mtk::atan(value));
}

} // namespace mtk

#endif
