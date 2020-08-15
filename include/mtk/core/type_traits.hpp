#ifndef MTK_CORE_TYPE_TRAITS_HPP
#define MTK_CORE_TYPE_TRAITS_HPP

//! @file
//! Contains traits for types.

#include <mtk/core/types.hpp>

#include <utility>

namespace mtk {

//! @defgroup type_traits mtk/core/type_traits.hpp
//! @{

namespace impl_core {

template<class T
	,class U>
struct copy_cv_helper
{
	using type = std::remove_cv_t<T>;
};

template<class T
	,class U>
struct copy_cv_helper<T, const U>
{
	using type = const std::remove_cv_t<T>;
};

template<class T
	,class U>
struct copy_cv_helper<T, volatile U>
{
	using type = volatile std::remove_cv_t<T>;
};

template<class T
	,class U>
struct copy_cv_helper<T, const volatile U>
{
	using type = const volatile std::remove_cv_t<T>;
};



template<class T
	,class U>
struct copy_reference_helper
{
	using type = std::remove_reference_t<T>;
};

template<class T
	,class U>
struct copy_reference_helper<T, U&>
{
	using type = std::remove_reference_t<T>&;
};

template<class T
	,class U>
struct copy_reference_helper<T, U&&>
{
	using type = std::remove_reference_t<T>&&;
};



template<class T
	,class U>
struct copy_pointer_helper
{
	using type = std::remove_pointer_t<T>;
};

template<class T
	,class U>
struct copy_pointer_helper<T, U*>
{
	using type = std::remove_pointer_t<T>*;
};



template<class T
	,class U
	,class = void>
struct copy_sign_helper { };

template<class T
	,class U>
struct copy_sign_helper<T, U
	,std::void_t<void
		,require<std::is_integral_v<T>>
		,require<std::is_integral_v<U>>
		,require<!std::is_same_v<std::decay_t<T>, bool>>
		,require<!std::is_same_v<std::decay_t<U>, bool>>
	>>
{
	using type = std::conditional_t<std::is_signed_v<U>, std::make_signed_t<T>, std::make_unsigned_t<T>>;
};



template<class T
	,class = void>
struct make_real_arith { };

template<class T>
struct make_real_arith<T
	,std::void_t<void
		,require<std::is_arithmetic_v<T>>
	>> : std::conditional<std::is_integral_v<T>, typename copy_cv_helper<real, T>::type, T> { };

template<class T
	,class = void>
struct make_real_helper :
	make_real_arith<T> { };

template<class T>
struct make_real_helper<T
	,std::void_t<void
		,typename T::value_type
		,decltype(std::declval<T&>().real())
		,decltype(std::declval<T&>().imag())
	>>
{
	using type = typename T::value_type;
};



template<class T
	,class = void>
struct promote_helper
{ };

template<class T>
using promote_integer_type = std::conditional_t<sizeof(T) < sizeof(short),
		short,
		std::conditional_t<sizeof(T) < sizeof(int),
			int,
			std::conditional_t<sizeof(T) < sizeof(long),
				long,
				std::conditional_t<sizeof(T) < sizeof(llong),
					llong,
					void>>>>;

template<class T>
using promote_floating_point_type = std::conditional_t<sizeof(T) < sizeof(double),
		double,
		std::conditional_t<sizeof(T) < sizeof(ldouble),
			ldouble,
			void>>;

template<class T>
struct promote_helper<T
	,std::void_t<void
		,require<std::is_integral_v<T> || std::is_floating_point_v<T>>
		,require<std::is_integral_v<T> || (sizeof(T) < sizeof(ldouble))>
		,require<std::is_floating_point_v<T> || (sizeof(T) < sizeof(llong))>
	>>
{
	using type = std::conditional_t<std::is_integral_v<T>,
		promote_integer_type<T>,
		promote_floating_point_type<T>>;
};

} // namespace impl_core



//! @brief Contains the member typedef type equal to T
//! with the cv-qualification of CV.
template<class T
	,class CV>
struct copy_cv
#ifndef MTK_DOXYGEN
	: impl_core::copy_cv_helper<T, CV>
#endif
{ };

//! @brief Contains the member typedef type equal to T
//! with the ref-qualification of Ref.
template<class T
	,class Ref>
struct copy_reference
#ifndef MTK_DOXYGEN
	: impl_core::copy_reference_helper<T, Ref>
#endif
{ };

//! @brief Contains the member typedef type equal to T
//! with the cvref-qualification of CVRef.
template<class T
	,class CVRef>
struct copy_cvref
#ifndef MTK_DOXYGEN
	: copy_reference<typename copy_cv<std::remove_reference_t<T>, std::remove_reference_t<CVRef>>::type, CVRef>
#endif
{ };

//! @brief Contains the member typedef type equal to T
//! with the pointer-qualification of Ptr.
template<class T
	,class Ptr>
struct copy_pointer
#ifndef MTK_DOXYGEN
	: impl_core::copy_pointer_helper<T, Ptr>
#endif
{ };



//! Shorthand for copy_cv::type.
template<class T
	,class CV>
using copy_cv_t = typename copy_cv<T, CV>::type;

//! Shorthand for copy_reference::type.
template<class T
	,class Ref>
using copy_reference_t = typename copy_reference<T, Ref>::type;

//! Shorthand for copy_cvref::type.
template<class T
	,class CVRef>
using copy_cvref_t = typename copy_cvref<T, CVRef>::type;

//! Shorthand for copy_pointer::type.
template<class T
	,class Ptr>
using copy_pointer_t = typename copy_pointer<T, Ptr>::type;



//! @brief Contains the member typedef type equal to T
//! with the same signness as Sign.
//!
//! @pre T and Sign must be integral types which is not bool.
template<class T
	,class Sign>
struct copy_sign
#ifndef MTK_DOXYGEN
	: impl_core::copy_sign_helper<T, Sign>
#endif
{ };

//! Shorthand for copy_sign::type.
template<class T
	,class Sign>
using copy_sign_t = typename copy_sign<T, Sign>::type;



//! @brief Contains the member typedef type equal to T if
//! T is a floating point type, else mtk::real if T is an integral
//! type, else U if T is std::complex<U>.
template<class T>
struct make_real
#ifndef MTK_DOXYGEN
	: impl_core::make_real_helper<T>
#endif
{ };

//! Shorthand for make_real::type.
template<class T>
using make_real_t = typename make_real<T>::type;



//! @brief Contains the member typedef type equal to a wider type than T.
//!
//! If T is an integral type then the member type is equal to a wider signed
//! integral type if exists, else type is not defined.
//! If T is a floating point type then the member type is equal to a wider
//! floating point type if exists, else type is not defined.
template<class T>
struct promote
#ifndef MTK_DOXYGEN
	: impl_core::promote_helper<T>
#endif
{ };

//! Shorthand for promote::type.
template<class T>
using promote_t = typename promote<T>::type;

//! @}

} // namespace mtk

#endif
