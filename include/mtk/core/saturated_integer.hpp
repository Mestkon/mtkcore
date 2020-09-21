#ifndef MTK_CORE_SATURATED_INTEGER_HPP
#define MTK_CORE_SATURATED_INTEGER_HPP

//! @file
//! Defines the saturated_integer class template.

#include <mtk/core/assert.hpp>
#include <mtk/core/casts.hpp>
#include <mtk/core/types.hpp>
#include <mtk/core/type_traits.hpp>

namespace mtk {

//! @defgroup sat_int mtk/core/saturated_integer.hpp
//! @{

//! @brief Defines integer types that does not overflow.
//!
//! std::numeric_limits is specialized for instantiations of
//! the saturated_integer template.
//!
//! @tparam T Integer type for which to add saturated operations.
//!
//! @pre T must be an integral type for which mtk::promote has a member type.
template<class T>
class saturated_integer
{
	static_assert(std::is_integral_v<T>);
public:
	//! Convenience typedef.
	using value_type = T;

	//! Default constructor. Value is uninitialized.
	saturated_integer() noexcept = default;

	//! Initialized to the given value.
	constexpr
	saturated_integer(T val) noexcept :
		m_val(val)
	{ }

	//! Returns the current value.
	constexpr
	T
	value() const noexcept
	{
		return m_val;
	}

	//! Returns the current value.
	explicit constexpr
	operator T() const noexcept
	{
		return m_val;
	}

	//! @relates saturated_integer
	friend constexpr
	bool
	operator==(saturated_integer lhs, saturated_integer rhs) noexcept
	{
		return (lhs.m_val == rhs.m_val);
	}

	//! @relates saturated_integer
	friend constexpr
	bool
	operator!=(saturated_integer lhs, saturated_integer rhs) noexcept
	{
		return (lhs.m_val != rhs.m_val);
	}

	//! @relates saturated_integer
	friend constexpr
	bool
	operator<(saturated_integer lhs, saturated_integer rhs) noexcept
	{
		return (lhs.m_val < rhs.m_val);
	}

	//! @relates saturated_integer
	friend constexpr
	bool
	operator>(saturated_integer lhs, saturated_integer rhs) noexcept
	{
		return (lhs.m_val > rhs.m_val);
	}

	//! @relates saturated_integer
	friend constexpr
	bool
	operator<=(saturated_integer lhs, saturated_integer rhs) noexcept
	{
		return (lhs.m_val <= rhs.m_val);
	}

	//! @relates saturated_integer
	friend constexpr
	bool
	operator>=(saturated_integer lhs, saturated_integer rhs) noexcept
	{
		return (lhs.m_val >= rhs.m_val);
	}

	//! @relates saturated_integer
	friend constexpr
	saturated_integer&
	operator++(saturated_integer& rhs) noexcept
	{
		constexpr auto max = std::numeric_limits<T>::max();
		if (rhs.m_val < max)
			++rhs.m_val;

		return rhs;
	}

	//! @relates saturated_integer
	friend constexpr
	saturated_integer
	operator++(saturated_integer& lhs, int) noexcept
	{
		const auto cp = lhs;
		++lhs;
		return cp;
	}

	//! @relates saturated_integer
	friend constexpr
	saturated_integer&
	operator--(saturated_integer& rhs) noexcept
	{
		constexpr auto min = std::numeric_limits<T>::min();
		if (rhs.m_val > min)
			--rhs.m_val;

		return rhs;
	}

	//! @relates saturated_integer
	friend constexpr
	saturated_integer
	operator--(saturated_integer& lhs, int) noexcept
	{
		const auto cp = lhs;
		--lhs;
		return cp;
	}

	//! @relates saturated_integer
	friend constexpr
	saturated_integer
	operator+(saturated_integer rhs) noexcept
	{
		return rhs;
	}

	//! @relates saturated_integer
	friend constexpr
	saturated_integer
	operator-(saturated_integer rhs) noexcept
	{
		using U = promote_t<T>;
		const auto new_val = -static_cast<U>(rhs.m_val);
		rhs.m_val = mtk::saturate_cast<T>(new_val);

		return rhs;
	}

	//! @relates saturated_integer
	friend constexpr
	saturated_integer&
	operator+=(saturated_integer& lhs, saturated_integer rhs) noexcept
	{
		using U = promote_t<T>;
		const auto new_val = static_cast<U>(lhs.m_val) + static_cast<U>(rhs.m_val);
		lhs.m_val = mtk::saturate_cast<T>(new_val);

		return lhs;
	}

	//! @relates saturated_integer
	friend constexpr
	saturated_integer&
	operator-=(saturated_integer& lhs, saturated_integer rhs) noexcept
	{
		using U = promote_t<T>;
		const auto new_val = static_cast<U>(lhs.m_val) - static_cast<U>(rhs.m_val);
		lhs.m_val = mtk::saturate_cast<T>(new_val);

		return lhs;
	}

	//! @relates saturated_integer
	friend constexpr
	saturated_integer
	operator+(saturated_integer lhs, saturated_integer rhs) noexcept
	{
		return (lhs += rhs);
	}

	//! @relates saturated_integer
	friend constexpr
	saturated_integer
	operator-(saturated_integer lhs, saturated_integer rhs) noexcept
	{
		return (lhs -= rhs);
	}

	//! @relates saturated_integer
	friend constexpr
	saturated_integer&
	operator*=(saturated_integer& lhs, saturated_integer rhs) noexcept
	{
		using U = copy_sign_t<promote_t<T>, T>;
		const auto new_val = static_cast<U>(lhs.m_val) * static_cast<U>(rhs.m_val);
		lhs.m_val = mtk::saturate_cast<T>(new_val);

		return lhs;
	}

	//! @relates saturated_integer
	friend constexpr
	saturated_integer&
	operator/=(saturated_integer& lhs, saturated_integer rhs) noexcept
	{
		MTK_IMPL_LIB_ASSERT(rhs.m_val != T());

		using U = promote_t<T>;
		const auto new_val = static_cast<U>(lhs.m_val) / static_cast<U>(rhs.m_val);
		lhs.m_val = mtk::saturate_cast<T>(new_val);

		return lhs;
	}

	//! @relates saturated_integer
	friend constexpr
	saturated_integer
	operator*(saturated_integer lhs, saturated_integer rhs) noexcept
	{
		return (lhs *= rhs);
	}

	//! @relates saturated_integer
	friend constexpr
	saturated_integer
	operator/(saturated_integer lhs, saturated_integer rhs) noexcept
	{
		return (lhs /= rhs);
	}

	//! @relates saturated_integer
	friend constexpr
	saturated_integer&
	operator%=(saturated_integer& lhs, saturated_integer rhs) noexcept
	{
		MTK_IMPL_LIB_ASSERT(rhs.m_val != T());

		using U = promote_t<T>;
		const auto new_val = static_cast<U>(lhs.m_val) % static_cast<U>(rhs.m_val);
		lhs.m_val = mtk::saturate_cast<T>(new_val);

		return lhs;
	}

	//! @relates saturated_integer
	friend constexpr
	saturated_integer
	operator%(saturated_integer lhs, saturated_integer rhs) noexcept
	{
		return (lhs %= rhs);
	}

private:
	T m_val;
};

#if defined(MTK_FIXED_WIDTH_INTS) || defined(MTK_DOXYGEN)

	inline namespace types {

	//! @addtogroup sat_int
	//! @{

	using int8_sat = saturated_integer<int8>; //!< Optional 8-bit saturated signed integer @sa MTK_FIXED_WIDTH_INTS
	using int16_sat = saturated_integer<int16>; //!< Optional 16-bit saturated signed integer @sa MTK_FIXED_WIDTH_INTS
	using int32_sat = saturated_integer<int32>; //!< Optional 32-bit saturated signed integer @sa MTK_FIXED_WIDTH_INTS

	using uint8_sat = saturated_integer<uint8>; //!< Optional 8-bit saturated unsigned integer @sa MTK_FIXED_WIDTH_INTS
	using uint16_sat = saturated_integer<uint16>; //!< Optional 16-bit saturated unsigned integer @sa MTK_FIXED_WIDTH_INTS
	using uint32_sat = saturated_integer<uint32>; //!< Optional 32-bit saturated unsigned integer @sa MTK_FIXED_WIDTH_INTS

	//! @}

	}

#endif

//! @}

} // namespace mtk

template<class T>
class std::numeric_limits<mtk::saturated_integer<T>>
{
	using base = std::numeric_limits<T>;
public:
	static constexpr auto is_specialized = true;
	static constexpr auto is_integer = base::is_integer;
	static constexpr auto is_exact = base::is_exact;
	static constexpr auto has_infinity = base::has_infinity;
	static constexpr auto has_quiet_NaN = base::has_quiet_NaN;
	static constexpr auto has_signaling_NaN = base::has_signaling_NaN;
	static constexpr auto has_denorm = base::has_denorm;
	static constexpr auto has_denorm_loss = base::has_denorm_loss;
	static constexpr auto round_style = base::round_style;
	static constexpr auto is_iec559 = base::is_iec559;
	static constexpr auto is_bounded = base::is_bounded;
	static constexpr auto is_modulo = false;
	static constexpr auto digits = base::digits;
	static constexpr auto digits10 = base::digits10;
	static constexpr auto max_digits10 = base::max_digits10;
	static constexpr auto radix = base::radix;
	static constexpr auto min_exponent = base::min_exponent;
	static constexpr auto min_exponent10 = base::min_exponent10;
	static constexpr auto max_exponent = base::max_exponent;
	static constexpr auto max_exponent10 = base::max_exponent10;
	static constexpr auto traps = base::traps;
	static constexpr auto tinyness_before = base::tinyness_before;

	static constexpr
	mtk::saturated_integer<T>
	min() noexcept
	{
		return base::min();
	}

	static constexpr
	mtk::saturated_integer<T>
	lowest() noexcept
	{
		return base::lowest();
	}

	static constexpr
	mtk::saturated_integer<T>
	max() noexcept
	{
		return base::max();
	}

	static constexpr
	mtk::saturated_integer<T>
	epsilon() noexcept
	{
		return base::epsilon();
	}

	static constexpr
	mtk::saturated_integer<T>
	round_error() noexcept
	{
		return base::round_error();
	}

	static constexpr
	mtk::saturated_integer<T>
	infinity() noexcept
	{
		return base::infinity();
	}

	static constexpr
	mtk::saturated_integer<T>
	quiet_NaN() noexcept
	{
		return base::quiet_NaN();
	}

	static constexpr
	mtk::saturated_integer<T>
	signaling_NaN() noexcept
	{
		return base::signaling_NaN();
	}

	static constexpr
	mtk::saturated_integer<T>
	denorm_min() noexcept
	{
		return base::denorm_min();
	}
};

#endif
