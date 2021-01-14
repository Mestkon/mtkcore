#ifndef MTK_CORE_TYPEPUN_CAST_HPP
#define MTK_CORE_TYPEPUN_CAST_HPP

//! @file
//! Contains typepun_cast.

#include <mtk/core/casts.hpp>
#include <mtk/core/types.hpp>

#ifndef MTK_DOXYGEN
	#if defined(__GNUC__)
		#define MTK_MEMCPY __builtin_memcpy
	#else
		#include <cstring>
		#define MTK_MEMCPY std::memcpy
	#endif
#endif

namespace mtk {

//! @defgroup tp_cast mtk/core/typepun_cast.hpp
//! @{

inline namespace casts {

//! @addtogroup tp_cast
//! @{

//! @brief Interprets the bits in the given instance of From
//! as an instance of To.
//!
//! Can be used instead of reinterpret_cast for type punning to avoid
//! undefined behavior.
//!
//! @code
//! int i = 42;
//! //float f = *reinterpret_cast<float*>(&i); // wrong, UB.
//! float f = mtk::typepun_cast<float>(i); // correct, not UB.
//! @endcode
//!
//! @pre sizeof(From) == sizeof(To).
//! @pre To must be nothrow default constructible.
//! @pre From must be trivially copyable.
//! @pre To must be trivially copyable.
template<class To
	,class From
#ifndef MTK_DOXYGEN
	,require<sizeof(To) == sizeof(From)> = 0
	,require<std::is_nothrow_default_constructible_v<To>> = 0
	,require<std::is_trivially_copyable_v<To>> = 0
	,require<std::is_trivially_copyable_v<From>> = 0
#endif
>
To
typepun_cast(const From& from) noexcept
{
	To ret;
	MTK_MEMCPY(mtk::addressof(ret), mtk::addressof(from), sizeof(To));
	return ret;
}

//! @}

} // namespace casts

//! @}

} // namespace mtk

#undef MTK_MEMCPY

#endif
