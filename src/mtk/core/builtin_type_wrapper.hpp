#ifndef MTK_CORE_BUILTIN_TYPE_WRAPPER_HPP
#define MTK_CORE_BUILTIN_TYPE_WRAPPER_HPP

#include <mtk/core/types.hpp>

namespace mtk {
namespace impl_core {

template<class T>
struct builtin_traits;
/// {
///		using type = /* builtin_type */;
///
///		static bool Eq(T, T);
///		static bool Lt(T, T);
///
///		static void Inc(T&);
///		static void Dec(T&);
///
///		static T Pos(T);
///		static T Neg(T);
///
///		static void Add(T&, T);
///		static void Sub(T&, T);
///		static void Mul(T&, T);
///		static void Div(T&, T);
///
///	Integers only below
///
///		static void Mod(T&, T);
///
///		static T Not(T);
///		static void And(T&, T);
///		static void Or(T&, T);
///		static void Xor(T&, T);
///
///		static void Ls(T&,
/// }


template<class Derived>
class builtin_type_wrapper
{
	static_assert(std::is_arithmetic_v<typename builtin_traits<Derived>::type>);
	static_assert(!std::is_const_v<typename builtin_traits<Derived>::type>);
	static_assert(!std::is_volatile_v<typename builtin_traits<Derived>::type>);
};



template<class D>
constexpr
bool
operator==(const builtin_type_wrapper<D>& lhs, const builtin_type_wrapper<D>& rhs)
{
	return builtin_traits<D>::Eq(static_cast<const D&>(lhs), static_cast<const D&>(rhs));
}

template<class D>
constexpr
bool
operator==(const builtin_type_wrapper<D>& lhs, typename builtin_traits<D>::type rhs)
{
	return (lhs == D(rhs));
}

template<class D>
constexpr
bool
operator==(typename builtin_traits<D>::type lhs, const builtin_type_wrapper<D>& rhs)
{
	return (D(lhs) == rhs);
}

template<class D
	,class U
	,require<!std::is_same_v<U, typename builtin_traits<D>::type>> = 0
	,require<!std::is_same_v<U, D>> = 0>
constexpr
bool
operator==(const builtin_type_wrapper<D>& lhs, U rhs) = delete;

template<class D
	,class U
	,require<!std::is_same_v<U, typename builtin_traits<D>::type>> = 0
	,require<!std::is_same_v<U, D>> = 0>
constexpr
bool
operator==(U lhs, const builtin_type_wrapper<D>& rhs) = delete;



template<class D>
constexpr
bool
operator!=(const builtin_type_wrapper<D>& lhs, const builtin_type_wrapper<D>& rhs)
{
	return !builtin_traits<D>::Eq(static_cast<const D&>(lhs), static_cast<const D&>(rhs));
}

template<class D>
constexpr
bool
operator!=(const builtin_type_wrapper<D>& lhs, typename builtin_traits<D>::type rhs)
{
	return (lhs != D(rhs));
}

template<class D>
constexpr
bool
operator!=(typename builtin_traits<D>::type lhs, const builtin_type_wrapper<D>& rhs)
{
	return (D(lhs) != rhs);
}

template<class D
	,class U
	,require<!std::is_same_v<U, typename builtin_traits<D>::type>> = 0
	,require<!std::is_same_v<U, D>> = 0>
constexpr
bool
operator!=(const builtin_type_wrapper<D>& lhs, U rhs) = delete;

template<class D
	,class U
	,require<!std::is_same_v<U, typename builtin_traits<D>::type>> = 0
	,require<!std::is_same_v<U, D>> = 0>
constexpr
bool
operator!=(U lhs, const builtin_type_wrapper<D>& rhs) = delete;



template<class D>
constexpr
bool
operator<(const builtin_type_wrapper<D>& lhs, const builtin_type_wrapper<D>& rhs)
{
	return builtin_traits<D>::Lt(static_cast<const D&>(lhs), static_cast<const D&>(rhs));
}

template<class D>
constexpr
bool
operator<(const builtin_type_wrapper<D>& lhs, typename builtin_traits<D>::type rhs)
{
	return (lhs < D(rhs));
}

template<class D>
constexpr
bool
operator<(typename builtin_traits<D>::type lhs, const builtin_type_wrapper<D>& rhs)
{
	return (D(lhs) < rhs);
}

template<class D
	,class U
	,require<!std::is_same_v<U, typename builtin_traits<D>::type>> = 0
	,require<!std::is_same_v<U, D>> = 0>
constexpr
bool
operator<(const builtin_type_wrapper<D>& lhs, U rhs) = delete;

template<class D
	,class U
	,require<!std::is_same_v<U, typename builtin_traits<D>::type>> = 0
	,require<!std::is_same_v<U, D>> = 0>
constexpr
bool
operator<(U lhs, const builtin_type_wrapper<D>& rhs) = delete;



template<class D>
constexpr
bool
operator>(const builtin_type_wrapper<D>& lhs, const builtin_type_wrapper<D>& rhs)
{
	return builtin_traits<D>::Lt(static_cast<const D&>(rhs), static_cast<const D&>(lhs));
}

template<class D>
constexpr
bool
operator>(const builtin_type_wrapper<D>& lhs, typename builtin_traits<D>::type rhs)
{
	return (lhs > D(rhs));
}

template<class D>
constexpr
bool
operator>(typename builtin_traits<D>::type lhs, const builtin_type_wrapper<D>& rhs)
{
	return (D(lhs) > rhs);
}

template<class D
	,class U
	,require<!std::is_same_v<U, typename builtin_traits<D>::type>> = 0
	,require<!std::is_same_v<U, D>> = 0>
constexpr
bool
operator>(const builtin_type_wrapper<D>& lhs, U rhs) = delete;

template<class D
	,class U
	,require<!std::is_same_v<U, typename builtin_traits<D>::type>> = 0
	,require<!std::is_same_v<U, D>> = 0>
constexpr
bool
operator>(U lhs, const builtin_type_wrapper<D>& rhs) = delete;



template<class D>
constexpr
bool
operator<=(const builtin_type_wrapper<D>& lhs, const builtin_type_wrapper<D>& rhs)
{
	return !builtin_traits<D>::Lt(static_cast<const D&>(rhs), static_cast<const D&>(lhs));
}

template<class D>
constexpr
bool
operator<=(const builtin_type_wrapper<D>& lhs, typename builtin_traits<D>::type rhs)
{
	return (lhs <= D(rhs));
}

template<class D>
constexpr
bool
operator<=(typename builtin_traits<D>::type lhs, const builtin_type_wrapper<D>& rhs)
{
	return (D(lhs) <= rhs);
}

template<class D
	,class U
	,require<!std::is_same_v<U, typename builtin_traits<D>::type>> = 0
	,require<!std::is_same_v<U, D>> = 0>
constexpr
bool
operator<=(const builtin_type_wrapper<D>& lhs, U rhs) = delete;

template<class D
	,class U
	,require<!std::is_same_v<U, typename builtin_traits<D>::type>> = 0
	,require<!std::is_same_v<U, D>> = 0>
constexpr
bool
operator<=(U lhs, const builtin_type_wrapper<D>& rhs) = delete;



template<class D>
constexpr
bool
operator>=(const builtin_type_wrapper<D>& lhs, const builtin_type_wrapper<D>& rhs)
{
	return !builtin_traits<D>::Lt(static_cast<const D&>(lhs), static_cast<const D&>(rhs));
}

template<class D>
constexpr
bool
operator>=(const builtin_type_wrapper<D>& lhs, typename builtin_traits<D>::type rhs)
{
	return (lhs >= D(rhs));
}

template<class D>
constexpr
bool
operator>=(typename builtin_traits<D>::type lhs, const builtin_type_wrapper<D>& rhs)
{
	return (D(lhs) >= rhs);
}

template<class D
	,class U
	,require<!std::is_same_v<U, typename builtin_traits<D>::type>> = 0
	,require<!std::is_same_v<U, D>> = 0>
constexpr
bool
operator>=(const builtin_type_wrapper<D>& lhs, U rhs) = delete;

template<class D
	,class U
	,require<!std::is_same_v<U, typename builtin_traits<D>::type>> = 0
	,require<!std::is_same_v<U, D>> = 0>
constexpr
bool
operator>=(U lhs, const builtin_type_wrapper<D>& rhs) = delete;



template<class D>
constexpr
D&
operator++(builtin_type_wrapper<D>& rhs)
{
	builtin_traits<D>::Inc(static_cast<D&>(rhs));
	return static_cast<D&>(rhs);
}

template<class D>
constexpr
D
operator++(builtin_type_wrapper<D>& lhs, int)
{
	D cp = static_cast<D&>(lhs);
	++lhs;
	return cp;
}



template<class D>
constexpr
D
operator+(const builtin_type_wrapper<D>& rhs)
{
	return builtin_traits<D>::Pos(static_cast<const D&>(rhs));
}

template<class D>
constexpr
D
operator-(const builtin_type_wrapper<D>& rhs)
{
	return builtin_traits<D>::Neg(static_cast<const D&>(rhs));
}



template<class D>
constexpr
D&
operator--(builtin_type_wrapper<D>& rhs)
{
	builtin_traits<D>::Dec(static_cast<D&>(rhs));
	return static_cast<D&>(rhs);
}

template<class D>
constexpr
D
operator--(builtin_type_wrapper<D>& lhs, int)
{
	D cp = static_cast<D&>(lhs);
	--lhs;
	return cp;
}



template<class D>
constexpr
D&
operator+=(builtin_type_wrapper<D>& lhs, const builtin_type_wrapper<D>& rhs)
{
	builtin_traits<D>::Add(static_cast<D&>(lhs), static_cast<const D&>(rhs));
	return static_cast<D&>(lhs);
}

template<class D>
constexpr
D&
operator+=(builtin_type_wrapper<D>& lhs, typename builtin_traits<D>::type rhs)
{
	return (lhs += D(rhs));
}

template<class D
	,class U
	,require<!std::is_same_v<U, typename builtin_traits<D>::type>> = 0
	,require<!std::is_same_v<U, D>> = 0>
constexpr
D&
operator+=(builtin_type_wrapper<D>& lhs, U rhs) = delete;



template<class D>
constexpr
D&
operator-=(builtin_type_wrapper<D>& lhs, const builtin_type_wrapper<D>& rhs)
{
	builtin_traits<D>::Sub(static_cast<D&>(lhs), static_cast<const D&>(rhs));
	return static_cast<D&>(lhs);
}

template<class D>
constexpr
D&
operator-=(builtin_type_wrapper<D>& lhs, typename builtin_traits<D>::type rhs)
{
	return (lhs -= D(rhs));
}

template<class D
	,class U
	,require<!std::is_same_v<U, typename builtin_traits<D>::type>> = 0
	,require<!std::is_same_v<U, D>> = 0>
constexpr
D&
operator-=(builtin_type_wrapper<D>& lhs, U rhs) = delete;



template<class D>
constexpr
D
operator+(const builtin_type_wrapper<D>& lhs, const builtin_type_wrapper<D>& rhs)
{
	D cp = static_cast<const D&>(lhs);
	return (cp += rhs);
}

template<class D>
constexpr
D
operator+(const builtin_type_wrapper<D>& lhs, typename builtin_traits<D>::type rhs)
{
	return (lhs + D(rhs));
}

template<class D>
constexpr
D
operator+(typename builtin_traits<D>::type lhs, const builtin_type_wrapper<D>& rhs)
{
	return (D(lhs) + rhs);
}

template<class D
	,class U
	,require<!std::is_same_v<U, typename builtin_traits<D>::type>> = 0
	,require<!std::is_same_v<U, D>> = 0>
constexpr
D
operator+(const builtin_type_wrapper<D>& lhs, U rhs) = delete;

template<class D
	,class U
	,require<!std::is_same_v<U, typename builtin_traits<D>::type>> = 0
	,require<!std::is_same_v<U, D>> = 0>
constexpr
D
operator+(U lhs, const builtin_type_wrapper<D>& rhs) = delete;



template<class D>
constexpr
D
operator-(const builtin_type_wrapper<D>& lhs, const builtin_type_wrapper<D>& rhs)
{
	D cp = static_cast<const D&>(lhs);
	return (cp -= rhs);
}

template<class D>
constexpr
D
operator-(const builtin_type_wrapper<D>& lhs, typename builtin_traits<D>::type rhs)
{
	return (lhs - D(rhs));
}

template<class D>
constexpr
D
operator-(typename builtin_traits<D>::type lhs, const builtin_type_wrapper<D>& rhs)
{
	return (D(lhs) - rhs);
}

template<class D
	,class U
	,require<!std::is_same_v<U, typename builtin_traits<D>::type>> = 0
	,require<!std::is_same_v<U, D>> = 0>
constexpr
D
operator-(const builtin_type_wrapper<D>& lhs, U rhs) = delete;

template<class D
	,class U
	,require<!std::is_same_v<U, typename builtin_traits<D>::type>> = 0
	,require<!std::is_same_v<U, D>> = 0>
constexpr
D
operator-(U lhs, const builtin_type_wrapper<D>& rhs) = delete;



template<class D>
constexpr
D&
operator*=(builtin_type_wrapper<D>& lhs, const builtin_type_wrapper<D>& rhs)
{
	builtin_traits<D>::Mul(static_cast<D&>(lhs), static_cast<const D&>(rhs));
	return static_cast<D&>(lhs);
}

template<class D>
constexpr
D&
operator*=(builtin_type_wrapper<D&> lhs, typename builtin_traits<D>::type rhs)
{
	return (lhs *= D(rhs));
}

template<class D
	,class U
	,require<!std::is_same_v<U, typename builtin_traits<D>::type>> = 0
	,require<!std::is_same_v<U, D>> = 0>
constexpr
D&
operator*=(builtin_type_wrapper<D>& lhs, U rhs) = delete;



template<class D>
constexpr
D&
operator/=(builtin_type_wrapper<D>& lhs, const builtin_type_wrapper<D>& rhs)
{
	builtin_traits<D>::Div(static_cast<D&>(lhs), static_cast<const D&>(rhs));
	return static_cast<D&>(lhs);
}

template<class D>
constexpr
D&
operator/=(builtin_type_wrapper<D&> lhs, typename builtin_traits<D>::type rhs)
{
	return (lhs /= D(rhs));
}

template<class D
	,class U
	,require<!std::is_same_v<U, typename builtin_traits<D>::type>> = 0
	,require<!std::is_same_v<U, D>> = 0>
constexpr
D&
operator/=(builtin_type_wrapper<D>& lhs, U rhs) = delete;



template<class D>
constexpr
D
operator*(const builtin_type_wrapper<D>& lhs, const builtin_type_wrapper<D>& rhs)
{
	D cp = static_cast<const D&>(lhs);
	return (cp *= rhs);
}

template<class D>
constexpr
D
operator*(const builtin_type_wrapper<D>& lhs, typename builtin_traits<D>::type rhs)
{
	return (lhs * D(rhs));
}

template<class D>
constexpr
D
operator*(typename builtin_traits<D>::type lhs, const builtin_type_wrapper<D>& rhs)
{
	return (D(lhs) * rhs);
}

template<class D
	,class U
	,require<!std::is_same_v<U, typename builtin_traits<D>::type>> = 0
	,require<!std::is_same_v<U, D>> = 0>
constexpr
D
operator*(const builtin_type_wrapper<D>& lhs, U rhs) = delete;

template<class D
	,class U
	,require<!std::is_same_v<U, typename builtin_traits<D>::type>> = 0
	,require<!std::is_same_v<U, D>> = 0>
constexpr
D
operator*(U lhs, const builtin_type_wrapper<D>& rhs) = delete;



template<class D>
constexpr
D
operator/(const builtin_type_wrapper<D>& lhs, const builtin_type_wrapper<D>& rhs)
{
	D cp = static_cast<const D&>(lhs);
	return (cp /= rhs);
}

template<class D>
constexpr
D
operator/(const builtin_type_wrapper<D>& lhs, typename builtin_traits<D>::type rhs)
{
	return (lhs / D(rhs));
}

template<class D>
constexpr
D
operator/(typename builtin_traits<D>::type lhs, const builtin_type_wrapper<D>& rhs)
{
	return (D(lhs) / rhs);
}

template<class D
	,class U
	,require<!std::is_same_v<U, typename builtin_traits<D>::type>> = 0
	,require<!std::is_same_v<U, D>> = 0>
constexpr
D
operator/(const builtin_type_wrapper<D>& lhs, U rhs) = delete;

template<class D
	,class U
	,require<!std::is_same_v<U, typename builtin_traits<D>::type>> = 0
	,require<!std::is_same_v<U, D>> = 0>
constexpr
D
operator/(U lhs, const builtin_type_wrapper<D>& rhs) = delete;



template<class D
	,require<std::is_integral_v<typename builtin_traits<D>::type>> = 0>
constexpr
D&
operator%=(builtin_type_wrapper<D>& lhs, const builtin_type_wrapper<D>& rhs)
{
	builtin_traits<D>::Mod(static_cast<D&>(lhs), static_cast<const D&>(rhs));
	return static_cast<D&>(lhs);
}

template<class D
	,require<std::is_integral_v<typename builtin_traits<D>::type>> = 0>
constexpr
D&
operator%=(builtin_type_wrapper<D>& lhs, typename builtin_traits<D>::type rhs)
{
	return (lhs %= D(rhs));
}

template<class D
	,class U
	,require<std::is_floating_point_v<typename builtin_traits<D>::type>> = 0>
constexpr
D&
operator%=(builtin_type_wrapper<D>& lhs, U rhs) = delete;

template<class D
	,class U
	,require<std::is_integral_v<typename builtin_traits<D>::type>> = 0
	,require<!std::is_same_v<U, typename builtin_traits<D>::type>> = 0
	,require<!std::is_same_v<U, D>> = 0>
constexpr
D&
operator%=(builtin_type_wrapper<D>& lhs, U rhs) = delete;



template<class D
	,require<std::is_integral_v<typename builtin_traits<D>::type>> = 0>
constexpr
D
operator%(const builtin_type_wrapper<D>& lhs, const builtin_type_wrapper<D>& rhs)
{
	D cp = static_cast<const D&>(lhs);
	return (cp %= rhs);
}

template<class D
	,require<std::is_integral_v<typename builtin_traits<D>::type>> = 0>
constexpr
D
operator%(const builtin_type_wrapper<D>& lhs, typename builtin_traits<D>::type rhs)
{
	return (lhs % D(rhs));
}

template<class D
	,require<std::is_integral_v<typename builtin_traits<D>::type>> = 0>
constexpr
D
operator%(typename builtin_traits<D>::type lhs, const builtin_type_wrapper<D>& rhs)
{
	return (D(lhs) % rhs);
}

template<class D
	,class U
	,require<std::is_floating_point_v<typename builtin_traits<D>::type>> = 0>
constexpr
D
operator%(builtin_type_wrapper<D>& lhs, U rhs) = delete;

template<class D
	,class U
	,require<!std::is_same_v<U, D>> = 0
	,require<std::is_floating_point_v<typename builtin_traits<D>::type>> = 0>
constexpr
D
operator%(U lhs, builtin_type_wrapper<D>& rhs) = delete;

template<class D
	,class U
	,require<std::is_integral_v<typename builtin_traits<D>::type>> = 0
	,require<!std::is_same_v<U, typename builtin_traits<D>::type>> = 0
	,require<!std::is_same_v<U, D>> = 0>
constexpr
D
operator%(const builtin_type_wrapper<D>& lhs, U rhs) = delete;

template<class D
	,class U
	,require<std::is_integral_v<typename builtin_traits<D>::type>> = 0
	,require<!std::is_same_v<U, typename builtin_traits<D>::type>> = 0
	,require<!std::is_same_v<U, D>> = 0>
constexpr
D
operator%(U lhs, const builtin_type_wrapper<D>& rhs) = delete;



template<class D
	,require<std::is_integral_v<typename builtin_traits<D>::type>> = 0>
constexpr
D
operator~(const builtin_type_wrapper<D>& rhs)
{
	return builtin_traits<D>::Not(static_cast<const D&>(rhs));
}

template<class D
	,require<std::is_floating_point_v<typename builtin_traits<D>::type>> = 0>
constexpr
D
operator~(const builtin_type_wrapper<D>& rhs) = delete;



template<class D
	,require<std::is_integral_v<typename builtin_traits<D>::type>> = 0>
constexpr
D&
operator&=(builtin_type_wrapper<D>& lhs, const builtin_type_wrapper<D>& rhs)
{
	builtin_traits<D>::And(static_cast<D&>(lhs), static_cast<const D&>(rhs));
	return static_cast<D&>(lhs);
}

template<class D
	,require<std::is_integral_v<typename builtin_traits<D>::type>> = 0>
constexpr
D&
operator&=(builtin_type_wrapper<D>& lhs, typename builtin_traits<D>::type rhs)
{
	return (lhs &= D(rhs));
}

template<class D
	,class U
	,require<std::is_floating_point_v<typename builtin_traits<D>::type>> = 0>
constexpr
D&
operator&=(builtin_type_wrapper<D>& lhs, U rhs) = delete;

template<class D
	,class U
	,require<std::is_integral_v<typename builtin_traits<D>::type>> = 0
	,require<!std::is_same_v<U, typename builtin_traits<D>::type>> = 0
	,require<!std::is_same_v<U, D>> = 0>
constexpr
D&
operator&=(builtin_type_wrapper<D>& lhs, U rhs) = delete;



template<class D
	,require<std::is_integral_v<typename builtin_traits<D>::type>> = 0>
constexpr
D
operator&(const builtin_type_wrapper<D>& lhs, const builtin_type_wrapper<D>& rhs)
{
	D cp = static_cast<const D&>(lhs);
	return (cp &= rhs);
}

template<class D
	,require<std::is_integral_v<typename builtin_traits<D>::type>> = 0>
constexpr
D
operator&(const builtin_type_wrapper<D>& lhs, typename builtin_traits<D>::type rhs)
{
	return (lhs & D(rhs));
}

template<class D
	,require<std::is_integral_v<typename builtin_traits<D>::type>> = 0>
constexpr
D
operator&(typename builtin_traits<D>::type lhs, const builtin_type_wrapper<D>& rhs)
{
	return (D(lhs) & rhs);
}

template<class D
	,class U
	,require<std::is_floating_point_v<typename builtin_traits<D>::type>> = 0>
constexpr
D
operator&(builtin_type_wrapper<D>& lhs, U rhs) = delete;

template<class D
	,class U
	,require<!std::is_same_v<U, D>> = 0
	,require<std::is_floating_point_v<typename builtin_traits<D>::type>> = 0>
constexpr
D
operator&(U lhs, builtin_type_wrapper<D>& rhs) = delete;

template<class D
	,class U
	,require<std::is_integral_v<typename builtin_traits<D>::type>> = 0
	,require<!std::is_same_v<U, typename builtin_traits<D>::type>> = 0
	,require<!std::is_same_v<U, D>> = 0>
constexpr
D
operator&(const builtin_type_wrapper<D>& lhs, U rhs) = delete;

template<class D
	,class U
	,require<std::is_integral_v<typename builtin_traits<D>::type>> = 0
	,require<!std::is_same_v<U, typename builtin_traits<D>::type>> = 0
	,require<!std::is_same_v<U, D>> = 0>
constexpr
D
operator&(U lhs, const builtin_type_wrapper<D>& rhs) = delete;



template<class D
	,require<std::is_integral_v<typename builtin_traits<D>::type>> = 0>
constexpr
D&
operator|=(builtin_type_wrapper<D>& lhs, const builtin_type_wrapper<D>& rhs)
{
	builtin_traits<D>::Or(static_cast<D&>(lhs), static_cast<const D&>(rhs));
	return static_cast<D&>(lhs);
}

template<class D
	,require<std::is_integral_v<typename builtin_traits<D>::type>> = 0>
constexpr
D&
operator|=(builtin_type_wrapper<D>& lhs, typename builtin_traits<D>::type rhs)
{
	return (lhs |= D(rhs));
}

template<class D
	,class U
	,require<std::is_floating_point_v<typename builtin_traits<D>::type>> = 0>
constexpr
D&
operator|=(builtin_type_wrapper<D>& lhs, U rhs) = delete;

template<class D
	,class U
	,require<std::is_integral_v<typename builtin_traits<D>::type>> = 0
	,require<!std::is_same_v<U, typename builtin_traits<D>::type>> = 0
	,require<!std::is_same_v<U, D>> = 0>
constexpr
D&
operator|=(builtin_type_wrapper<D>& lhs, U rhs) = delete;



template<class D
	,require<std::is_integral_v<typename builtin_traits<D>::type>> = 0>
constexpr
D
operator|(const builtin_type_wrapper<D>& lhs, const builtin_type_wrapper<D>& rhs)
{
	D cp = static_cast<const D&>(lhs);
	return (cp |= rhs);
}

template<class D
	,require<std::is_integral_v<typename builtin_traits<D>::type>> = 0>
constexpr
D
operator|(const builtin_type_wrapper<D>& lhs, typename builtin_traits<D>::type rhs)
{
	return (lhs | D(rhs));
}

template<class D
	,require<std::is_integral_v<typename builtin_traits<D>::type>> = 0>
constexpr
D
operator|(typename builtin_traits<D>::type lhs, const builtin_type_wrapper<D>& rhs)
{
	return (D(lhs) | rhs);
}

template<class D
	,class U
	,require<std::is_floating_point_v<typename builtin_traits<D>::type>> = 0>
constexpr
D
operator|(builtin_type_wrapper<D>& lhs, U rhs) = delete;

template<class D
	,class U
	,require<!std::is_same_v<U, D>> = 0
	,require<std::is_floating_point_v<typename builtin_traits<D>::type>> = 0>
constexpr
D
operator|(U lhs, builtin_type_wrapper<D>& rhs) = delete;

template<class D
	,class U
	,require<std::is_integral_v<typename builtin_traits<D>::type>> = 0
	,require<!std::is_same_v<U, typename builtin_traits<D>::type>> = 0
	,require<!std::is_same_v<U, D>> = 0>
constexpr
D
operator|(const builtin_type_wrapper<D>& lhs, U rhs) = delete;

template<class D
	,class U
	,require<std::is_integral_v<typename builtin_traits<D>::type>> = 0
	,require<!std::is_same_v<U, typename builtin_traits<D>::type>> = 0
	,require<!std::is_same_v<U, D>> = 0>
constexpr
D
operator|(U lhs, const builtin_type_wrapper<D>& rhs) = delete;



template<class D
	,require<std::is_integral_v<typename builtin_traits<D>::type>> = 0>
constexpr
D&
operator^=(builtin_type_wrapper<D>& lhs, const builtin_type_wrapper<D>& rhs)
{
	builtin_traits<D>::Xor(static_cast<D&>(lhs), static_cast<const D&>(rhs));
	return static_cast<D&>(lhs);
}

template<class D
	,require<std::is_integral_v<typename builtin_traits<D>::type>> = 0>
constexpr
D&
operator^=(builtin_type_wrapper<D>& lhs, typename builtin_traits<D>::type rhs)
{
	return (lhs ^= D(rhs));
}

template<class D
	,class U
	,require<std::is_floating_point_v<typename builtin_traits<D>::type>> = 0>
constexpr
D&
operator^=(builtin_type_wrapper<D>& lhs, U rhs) = delete;

template<class D
	,class U
	,require<std::is_integral_v<typename builtin_traits<D>::type>> = 0
	,require<!std::is_same_v<U, typename builtin_traits<D>::type>> = 0
	,require<!std::is_same_v<U, D>> = 0>
constexpr
D&
operator^=(builtin_type_wrapper<D>& lhs, U rhs) = delete;



template<class D
	,require<std::is_integral_v<typename builtin_traits<D>::type>> = 0>
constexpr
D
operator^(const builtin_type_wrapper<D>& lhs, const builtin_type_wrapper<D>& rhs)
{
	D cp = static_cast<const D&>(lhs);
	return (cp ^= rhs);
}

template<class D
	,require<std::is_integral_v<typename builtin_traits<D>::type>> = 0>
constexpr
D
operator^(const builtin_type_wrapper<D>& lhs, typename builtin_traits<D>::type rhs)
{
	return (lhs ^ D(rhs));
}

template<class D
	,require<std::is_integral_v<typename builtin_traits<D>::type>> = 0>
constexpr
D
operator^(typename builtin_traits<D>::type lhs, const builtin_type_wrapper<D>& rhs)
{
	return (D(lhs) ^ rhs);
}

template<class D
	,class U
	,require<std::is_floating_point_v<typename builtin_traits<D>::type>> = 0>
constexpr
D
operator^(builtin_type_wrapper<D>& lhs, U rhs) = delete;

template<class D
	,class U
	,require<!std::is_same_v<U, D>> = 0
	,require<std::is_floating_point_v<typename builtin_traits<D>::type>> = 0>
constexpr
D
operator^(U lhs, builtin_type_wrapper<D>& rhs) = delete;

template<class D
	,class U
	,require<std::is_integral_v<typename builtin_traits<D>::type>> = 0
	,require<!std::is_same_v<U, typename builtin_traits<D>::type>> = 0
	,require<!std::is_same_v<U, D>> = 0>
constexpr
D
operator^(const builtin_type_wrapper<D>& lhs, U rhs) = delete;

template<class D
	,class U
	,require<std::is_integral_v<typename builtin_traits<D>::type>> = 0
	,require<!std::is_same_v<U, typename builtin_traits<D>::type>> = 0
	,require<!std::is_same_v<U, D>> = 0>
constexpr
D
operator^(U lhs, const builtin_type_wrapper<D>& rhs) = delete;



} // namespace impl_core
} // namespace mtk

#endif
