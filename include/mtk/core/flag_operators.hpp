#ifndef MTK_CORE_FLAG_OPERATORS_HPP
#define MTK_CORE_FLAG_OPERATORS_HPP

//! @file
//! Contains code to turn enum class into flags.

#include <mtk/core/preprocessor.hpp>

#include <type_traits>

namespace mtk {

//! @defgroup flag_op mtk/core/flag_operators.hpp
//! @{

#define MTK_IMPL_FLAG_OPERATOR(ENUM, OP) \
	constexpr \
	ENUM \
	operator OP (ENUM lhs, ENUM rhs) noexcept \
	{ \
		using _mtk_type = std::underlying_type_t<ENUM>; \
		return static_cast<ENUM>(static_cast<_mtk_type>(lhs) OP static_cast<_mtk_type>(rhs)); \
	} \
	constexpr \
 	ENUM& \
	operator MTK_CONCAT(OP, =) (ENUM& lhs, ENUM rhs) noexcept \
	{ \
		lhs = (lhs OP rhs); \
		return lhs; \
	}

//! @brief Overloads the flag operators for the supplied enum class type.
//!
//! @pre ENUM must be an enum class for which the flag operators
//! |, |=, &, &=, ^, ^=, and ~ are not defined.
#define MTK_DEFINE_FLAG_OPERATORS(ENUM) \
	static_assert(std::is_enum_v<ENUM>, "ENUM must be an enum class type"); \
	static_assert(!std::is_convertible_v<ENUM, std::underlying_type_t<ENUM>>, "ENUM must be an enum class type"); \
	MTK_IMPL_FLAG_OPERATOR(ENUM, |) \
	MTK_IMPL_FLAG_OPERATOR(ENUM, &) \
	MTK_IMPL_FLAG_OPERATOR(ENUM, ^) \
	constexpr ENUM operator~(ENUM rhs) noexcept \
	{ \
		using _mtk_type = std::underlying_type_t<ENUM>; \
		return static_cast<ENUM>(~static_cast<_mtk_type>(rhs)); \
	}

//! @}

} // namespace mtk

#endif
