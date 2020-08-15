#ifndef MTK_CORE_ITERATOR_TRAITS_HPP
#define MTK_CORE_ITERATOR_TRAITS_HPP

//! @file
//! Contains type traits for iterators.

#include <mtk/core/types.hpp>

#include <iterator>
#include <utility>

namespace mtk {

//! @defgroup iterator_traits mtk/core/iterator_traits.hpp
//! @{

//! Namespace to shorten std::iterator_traits
namespace iter {

//! @addtogroup iterator_traits
//! @{

//! Shorthand for std::iterator_traits::value_type.
template<class T>
using value = typename std::iterator_traits<T>::value_type;
//! Shorthand for std::iterator_traits::difference_type.
template<class T>
using difference = typename std::iterator_traits<T>::difference_type;
//! Shorthand for std::iterator_traits::reference.
template<class T>
using reference = typename std::iterator_traits<T>::reference;
//! Shorthand for std::iterator_traits::pointer.
template<class T>
using pointer = typename std::iterator_traits<T>::pointer;
//! Shorthand for std::iterator_traits::iterator_category.
template<class T>
using category = typename std::iterator_traits<T>::iterator_category;

//! @}

} // namespace iter



namespace impl_core {

template<class T
	,class = void>
struct is_iterator_helper : std::false_type { };

template<class T>
struct is_iterator_helper<T
	,std::void_t<void
		,require<std::is_copy_constructible_v<T>>
		,require<std::is_copy_assignable_v<T>>
		,require<std::is_destructible_v<T>>
		,require<std::is_swappable_v<T>>
		,iter::value<T>
		,iter::difference<T>
		,iter::reference<T>
		,iter::pointer<T>
		,iter::category<T>
		,decltype(*std::declval<T&>())
		,require<std::is_same_v<decltype(++std::declval<T&>()), T&>>
	>> : std::true_type { };



template<class T
	,class = void>
struct has_indirection : std::false_type { };

template<class T>
struct has_indirection<T*> : std::true_type { };

template<class T>
struct has_indirection<T
	,std::void_t<void
		,decltype(std::declval<T>().operator->())
	>> : std::true_type { };

template<class T
	,class = void>
struct is_input_iterator_helper : std::false_type { };

template<class T>
struct is_input_iterator_helper<T
	,std::void_t<void
		,require<is_iterator_helper<T>::value>
		,require<std::is_base_of_v<std::input_iterator_tag, iter::category<T>>>
		,require<std::is_convertible_v<decltype(std::declval<const T>() == std::declval<const T>()), bool>>
		,require<std::is_constructible_v<bool, decltype(std::declval<const T>() != std::declval<const T>())>>
		,require<std::is_same_v<decltype(*std::declval<const T>()), iter::reference<T>>>
		,require<has_indirection<T>::value>
		,require<std::is_convertible_v<iter::reference<T>, iter::value<T>>>
		,require<std::is_convertible_v<decltype(*std::declval<T&>()++), iter::value<T>>>
	>> : std::true_type { };



template<class T
	,class OutputT
	,class = void>
struct is_output_iterator_helper : std::false_type { };

template<class T
	,class OutputT>
struct is_output_iterator_helper<T
	,OutputT
	,std::void_t<void
		,require<is_iterator_helper<T>::value>
		,require<std::is_class_v<T> || std::is_pointer_v<T>>
		,decltype(*(std::declval<T&>()) = std::declval<OutputT>())
		,require<std::is_convertible_v<decltype(std::declval<T&>()++), const T&>>
		,decltype(*std::declval<T&>()++ = std::declval<OutputT>())
	>> : std::true_type { };



template<class T
	,class = void>
struct is_forward_iterator_helper : std::false_type { };

template<class T>
struct is_forward_iterator_helper<T
	,std::void_t<void
		,require<is_input_iterator_helper<T>::value>
		,require<std::is_base_of_v<std::forward_iterator_tag, iter::category<T>>>
		,require<std::is_default_constructible_v<T>>
		,require<std::is_same_v<iter::reference<T>, iter::value<T>&>
			|| std::is_same_v<iter::reference<T>, const iter::value<T>&>>
		,require<std::is_same_v<decltype(std::declval<T&>()++), T>>
		,require<std::is_same_v<decltype(*std::declval<T&>()++), iter::reference<T>>>
	>> : std::true_type { };



template<class T
	,class = void>
struct is_bidirectional_iterator_helper : std::false_type { };

template<class T>
struct is_bidirectional_iterator_helper<T
	,std::void_t<void
		,require<is_forward_iterator_helper<T>::value>
		,require<std::is_base_of_v<std::bidirectional_iterator_tag, iter::category<T>>>
		,require<std::is_same_v<decltype(--std::declval<T&>()), T&>>
		,require<std::is_convertible_v<decltype(std::declval<T&>()--), const T&>>
		,require<std::is_same_v<decltype(*std::declval<T&>()--), iter::reference<T>>>
	>> : std::true_type { };



template<class T
	,class = void>
struct is_random_access_iterator_helper : std::false_type { };

template<class T>
struct is_random_access_iterator_helper<T
	,std::void_t<void
		,require<is_bidirectional_iterator_helper<T>::value>
		,require<std::is_base_of_v<std::random_access_iterator_tag, iter::category<T>>>
		,require<std::is_same_v<decltype(std::declval<T&>() += std::declval<iter::difference<T>>()), T&>>
		,require<std::is_same_v<decltype(std::declval<const T>() + std::declval<iter::difference<T>>()), T>>
		,require<std::is_same_v<decltype(std::declval<iter::difference<T>>() + std::declval<const T>()), T>>
		,require<std::is_same_v<decltype(std::declval<T&>() -= std::declval<iter::difference<T>>()), T&>>
		,require<std::is_same_v<decltype(std::declval<const T>() - std::declval<iter::difference<T>>()), T>>
		,require<std::is_same_v<decltype(std::declval<const T>() - std::declval<const T>()), iter::difference<T>>>
		,require<std::is_convertible_v<decltype(std::declval<const T>()[std::declval<iter::difference<T>>()]), iter::reference<T>>>
		,require<std::is_constructible_v<bool, decltype(std::declval<const T>() < std::declval<const T>())>>
		,require<std::is_constructible_v<bool, decltype(std::declval<const T>() > std::declval<const T>())>>
		,require<std::is_constructible_v<bool, decltype(std::declval<const T>() >= std::declval<const T>())>>
		,require<std::is_constructible_v<bool, decltype(std::declval<const T>() <= std::declval<const T>())>>
	>> : std::true_type { };



template<class Sentinel
	,class Iterator
	,class = void>
struct is_sentinel_for_helper : std::false_type {  };

template<class Sentinel
	,class Iterator>
struct is_sentinel_for_helper<Sentinel, Iterator
	,std::void_t<void
		,require<is_input_iterator_helper<Iterator>::value>
		,require<std::is_copy_constructible_v<Sentinel>>
		,require<std::is_copy_assignable_v<Sentinel>>
		,require<std::is_default_constructible_v<Sentinel>>
		,require<std::is_constructible_v<bool, decltype(std::declval<const Iterator>() == std::declval<const Sentinel>())>>
		,require<std::is_constructible_v<bool, decltype(std::declval<const Iterator>() != std::declval<const Sentinel>())>>
		,require<std::is_constructible_v<bool, decltype(std::declval<const Sentinel>() == std::declval<const Iterator>())>>
		,require<std::is_constructible_v<bool, decltype(std::declval<const Sentinel>() != std::declval<const Iterator>())>>
	>> : std::true_type { };



} // namespace impl_core



//! @brief Trait to check if a given type conforms to the
//! Iterator named requirement.
//!
//! Provides the member constant value equal to true if conformant,
//! else false.
template<class T>
struct is_iterator
#ifndef MTK_DOXYGEN
	:impl_core::is_iterator_helper<T>
#endif
{ };

//! @brief Trait to check if a given type conforms to the
//! InputIterator named requirement.
//!
//! Provides the member constant value equal to true if conformant,
//! else false.
template<class T>
struct is_input_iterator
#ifndef MTK_DOXYGEN
	:impl_core::is_input_iterator_helper<T>
#endif
{ };

//! @brief Trait to check if a given type conforms to the
//! OutputIterator named requirement.
//!
//! Provides the member constant value equal to true if conformant,
//! with OutputT as the consumed type else false.
template<class T
	,class OutputT>
struct is_output_iterator
#ifndef MTK_DOXYGEN
	:impl_core::is_output_iterator_helper<T, OutputT>
#endif
{ };

//! @brief Trait to check if a given type conforms to the
//! ForwardIterator named requirement.
//!
//! Provides the member constant value equal to true if conformant,
//! else false.
template<class T>
struct is_forward_iterator
#ifndef MTK_DOXYGEN
	:impl_core::is_forward_iterator_helper<T>
#endif
{ };

//! @brief Trait to check if a given type conforms to the
//! BidirectionalIterator named requirement.
//!
//! Provides the member constant value equal to true if conformant,
//! else false.
template<class T>
struct is_bidirectional_iterator
#ifndef MTK_DOXYGEN
	:impl_core::is_bidirectional_iterator_helper<T>
#endif
{ };

//! @brief Trait to check if a given type conforms to the
//! RandomAccessIterator named requirement.
//!
//! Provides the member constant value equal to true if conformant,
//! else false.
template<class T>
struct is_random_access_iterator
#ifndef MTK_DOXYGEN
	:impl_core::is_random_access_iterator_helper<T>
#endif
{ };

//! @brief Trait to check if a given type can be used as a
//! sentinel for the given iterator.
//!
//! Provides the member constant value equal to true if it
//! can, else false.
template<class Sentinel
	,class Iterator>
struct is_sentinel_for
#ifndef MTK_DOXYGEN
	:impl_core::is_sentinel_for_helper<Sentinel, Iterator>
#endif
{ };



//! Shorthand for is_iterator::value.
template<class T>
inline constexpr
bool
is_iterator_v = is_iterator<T>::value;

//! Shorthand is_input_iterator::value.
template<class T>
inline constexpr
bool
is_input_iterator_v = is_input_iterator<T>::value;

//! Shorthand for is_output_iterator::value.
template<class T
	,class OutputT>
inline constexpr
bool
is_output_iterator_v = is_output_iterator<T, OutputT>::value;

//! Shorthand for is_forward_iterator::value.
template<class T>
inline constexpr
bool
is_forward_iterator_v = is_forward_iterator<T>::value;

//! Shorthand for is_bidirectional_iterator::value.
template<class T>
inline constexpr
bool
is_bidirectional_iterator_v = is_bidirectional_iterator<T>::value;

//! Shorthand for is_random_access_iterator::value.
template<class T>
inline constexpr
bool
is_random_access_iterator_v = is_random_access_iterator<T>::value;

//! Shorthand for is_sentinel_for::value.
template<class Sentinel
	,class Iterator>
inline constexpr
bool
is_sentinel_for_v = is_sentinel_for<Sentinel, Iterator>::value;

//! @}

} // namespace mtk

#endif
