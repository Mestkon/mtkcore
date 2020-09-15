#ifndef MTK_CORE_TYPES_HPP
#define MTK_CORE_TYPES_HPP

//! @file
//! Contains common useful typedefs.

#include <cstddef>
#include <cstdint>
#include <type_traits>

namespace mtk {

//! @defgroup types mtk/core/types.hpp
//! @{

#ifdef MTK_DOXYGEN
	//! @brief Define project-wide to include everything in mtk::types
	//! into the global namespace.
	#define MTK_GLOBAL_TYPES
#endif

//! Inline namespace for convenience typedefs.
inline namespace types {

//! @addtogroup types
//! @{

using llong = long long; //!< Shorthand.
using ldouble = long double; //!< Shorthand.

using schar = signed char; //!< Shorthand.

using uchar = unsigned char; //!< Shorthand.
using ushort = unsigned short; //!< Shorthand.
using uint = unsigned int; //!< Shorthand.
using ulong = unsigned long; //!< Shorthand.
using ullong = unsigned long long; //!< Shorthand.

using byte = uchar; //!< Typedef for documentation purposes.
using real = double; //!< Ideal floating point type.

using size_t = std::size_t; //!< Import into types.
using ssize_t = std::conditional_t<(sizeof(size_t) <= sizeof(long)), std::make_signed_t<size_t>, long>; //!< Equal to POSIX ssize_t
using ptrdiff_t = std::ptrdiff_t; //!< Import into types.



#if (defined(INT8_MAX) && defined(INT16_MAX) && defined(INT32_MAX) && defined(INT64_MAX) && \
	defined(UINT8_MAX) && defined(UINT16_MAX) && defined(UINT32_MAX) && defined(UINT64_MAX)) || \
	defined(MTK_DOXYGEN)

	 //! @brief Defined if the optional types in mtk::types are available.
	 //!
	 //! Same as the equivalent types in <cstdint> but can be imported to the current scope by
	 //! @code
	 //! using namespace mtk::types;
	 //! @endcode
	#define MTK_FIXED_WIDTH_INTS


	using int8 = std::int8_t; //!< Optional 8-bit signed integer @sa MTK_FIXED_WIDTH_INTS
	using int16 = std::int16_t; //!< Optional 16-bit signed integer @sa MTK_FIXED_WIDTH_INTS
	using int32 = std::int32_t; //!< Optional 32-bit signed integer @sa MTK_FIXED_WIDTH_INTS
	using int64 = std::int64_t; //!< Optional 64-bit signed integer @sa MTK_FIXED_WIDTH_INTS

	using uint8 = std::uint8_t; //!< Optional 8-bit unsigned integer @sa MTK_FIXED_WIDTH_INTS
	using uint16 = std::uint16_t; //!< Optional 16-bit unsigned integer @sa MTK_FIXED_WIDTH_INTS
	using uint32 = std::uint32_t; //!< Optional 32-bit unsigned integer @sa MTK_FIXED_WIDTH_INTS
	using uint64 = std::uint64_t; //!< Optional 64-bit unsigned integer @sa MTK_FIXED_WIDTH_INTS
#endif

//! @}

} // namespace types



//! @brief Simple typedef for SFINAE
//! @code
//! template<class T,
//!  mtk::require<std::is_integral_v<T>> = 0>
//! T func(T val);
//! @endcode
template<bool Cond>
using require = std::enable_if_t<Cond, int>;


} // namespace mtk


#ifdef MTK_GLOBAL_TYPES
	using namespace mtk::types;
#endif

#endif
