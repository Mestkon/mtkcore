#ifndef MTK_CORE_CONTAINER_TRAITS_HPP
#define MTK_CORE_CONTAINER_TRAITS_HPP

//! @file
//! Contains type traits for containers.

#include <mtk/core/allocator_traits.hpp>
#include <mtk/core/iterator_traits.hpp>

namespace mtk {

//! @defgroup container_traits mtk/core/container_traits.hpp
//! @{

namespace impl_core {

template<class T
	,class = void>
struct container_traits_basic { };

template<class T>
struct container_traits_basic<T[]>
{
	using value_type = std::remove_cv_t<T>;
	using reference = T&;
	using const_reference = const T&;
	using iterator = T*;
	using const_iterator = const T*;
	using difference_type = ptrdiff_t;
	using size_type = size_t;
};

template<class T
	,size_t N>
struct container_traits_basic<T[N]> :
	container_traits_basic<T[]> { };

template<class T>
struct container_traits_basic<T
	,std::void_t<void
		,typename T::value_type
		,typename T::reference
		,typename T::const_reference
		,typename T::iterator
		,typename T::const_iterator
		,typename T::difference_type
		,typename T::size_type
	>>
{
	using value_type = typename T::value_type;
	using reference = std::conditional_t<std::is_const_v<T>
		,typename T::const_reference
		,typename T::reference>;
	using const_reference = typename T::const_reference;
	using iterator = std::conditional_t<std::is_const_v<T>
		,typename T::const_iterator
		,typename T::iterator>;
	using const_iterator = typename T::const_iterator;
	using difference_type = typename T::difference_type;
	using size_type = typename T::size_type;
};



template<class T
	,class = void
	,class = void>
struct container_traits_pointer { };

template<class T
	,class U>
struct container_traits_pointer<T
	,U
	,std::void_t<void
		,typename container_traits_basic<T>::value_type
	>>
{
	using pointer = std::conditional_t<std::is_const_v<T>
		,const typename container_traits_basic<T>::value_type*
		,typename container_traits_basic<T>::value_type*>;
	using const_pointer = const typename container_traits_basic<T>::value_type*;
};

template<class T>
struct container_traits_pointer<T
	,void
	,std::void_t<void
		,typename container_traits_basic<T>::value_type
		,typename T::pointer
		,typename T::const_pointer
	>>
{
	using pointer = std::conditional_t<std::is_const_v<T>
		,typename T::const_pointer
		,typename T::pointer>;
	using const_pointer = typename T::const_pointer;
};





template<class T
	,class = void>
struct container_traits_reversible { };

template<class T>
struct container_traits_reversible<T[]>
{
	using reverse_iterator = std::reverse_iterator<T*>;
	using const_reverse_iterator = std::reverse_iterator<const T*>;
};

template<class T
	,size_t N>
struct container_traits_reversible<T[N]> :
	container_traits_reversible<T[]> { };

template<class T>
struct container_traits_reversible<T
	,std::void_t<void
		,typename container_traits_basic<T>::value_type
		,typename T::reverse_iterator
		,typename T::const_reverse_iterator
	>>
{
	using reverse_iterator = std::conditional_t<std::is_const_v<T>
		,typename T::const_reverse_iterator
		,typename T::reverse_iterator>;
	using const_reverse_iterator = typename T::const_reverse_iterator;
};



template<class T
	,class = void>
struct container_traits_allocator_aware { };

template<class T>
struct container_traits_allocator_aware<T
	,std::void_t<void
		,typename T::allocator_type
	>>
{
	using allocator_type = typename T::allocator_type;
};

} // namespace impl_core



//! @brief Analogue to std::iterator_traits, but for containers.
//!
//! Defines the following types if T is a container type: value_type, reference, const_reference,
//! pointer, const_pointer, iterator, const_iterator, difference_type, and size_type.
//!
//! Defines the following types if T is a reversible container type: reverse_iterator, and
//! const_reverse_iterator.
//!
//! Defines the following type if T is an allocator aware container type: allocator_type.
//!
//! container_traits is specialized for T[] and T[N] to support the container types
//! and the reversible container types.
template<class T>
struct container_traits
#ifndef MTK_DOXYGEN
	:impl_core::container_traits_basic<T>
	,impl_core::container_traits_pointer<T>
	,impl_core::container_traits_reversible<T>
	,impl_core::container_traits_allocator_aware<T>
#endif
{ };



//! Namespace to shorten mtk::container_traits
namespace cont {

//! @addtogroup container_traits
//! @{

//! Shorthand for mtk::container_traits::value_type.
template<class T>
using value = typename container_traits<T>::value_type;
//! Shorthand for mtk::container_traits::reference.
template<class T>
using reference = typename container_traits<T>::reference;
//! Shorthand for mtk::container_traits::const_reference.
template<class T>
using creference = typename container_traits<T>::const_reference;
//! Shorthand for mtk::container_traits::pointer.
template<class T>
using pointer = typename container_traits<T>::pointer;
//! Shorthand for mtk::container_traits::const_pointer.
template<class T>
using cpointer = typename container_traits<T>::const_pointer;
//! Shorthand for mtk::container_traits::iterator.
template<class T>
using iterator = typename container_traits<T>::iterator;
//! Shorthand for mtk::container_traits::const_iterator.
template<class T>
using citerator = typename container_traits<T>::const_iterator;
//! Shorthand for mtk::container_traits::difference_type.
template<class T>
using difference = typename container_traits<T>::difference_type;
//! Shorthand for mtk::container_traits::size_type.
template<class T>
using size = typename container_traits<T>::size_type;
//! Shorthand for mtk::container_traits::reverse_iterator.
template<class T>
using riterator = typename container_traits<T>::reverse_iterator;
//! Shorthand for mtk::container_traits::const_reverse_iterator.
template<class T>
using criterator = typename container_traits<T>::const_reverse_iterator;
//! Shorthand for mtk::container_traits::allocator_type.
template<class T>
using allocator = typename container_traits<T>::allocator_type;

//! @}

} // namespace cont



namespace impl_core {

template<class It
	,class CIt
	,class = void>
struct is_fwd_iters_interchangable : std::false_type { };

template<class It
	,class CIt>
struct is_fwd_iters_interchangable<It, CIt
	,std::void_t<void
		,require<std::is_convertible_v<decltype(std::declval<const It>() == std::declval<const CIt>()), bool>>
		,require<std::is_convertible_v<decltype(std::declval<const CIt>() == std::declval<const It>()), bool>>
		,require<std::is_constructible_v<bool, decltype(std::declval<const It>() != std::declval<const CIt>())>>
		,require<std::is_constructible_v<bool, decltype(std::declval<const CIt>() != std::declval<const It>())>>
	>> : std::true_type { };

template<class It
	,class CIt
	,class = void>
struct is_ra_iters_interchangable : std::false_type { };

template<class It
	,class CIt>
struct is_ra_iters_interchangable<It, CIt
	,std::void_t<void
		,require<std::is_constructible_v<bool, decltype(std::declval<const It>() < std::declval<const CIt>())>>
		,require<std::is_constructible_v<bool, decltype(std::declval<const CIt>() < std::declval<const It>())>>
		,require<std::is_constructible_v<bool, decltype(std::declval<const It>() > std::declval<const CIt>())>>
		,require<std::is_constructible_v<bool, decltype(std::declval<const CIt>() > std::declval<const It>())>>
		,require<std::is_constructible_v<bool, decltype(std::declval<const It>() <= std::declval<const CIt>())>>
		,require<std::is_constructible_v<bool, decltype(std::declval<const CIt>() <= std::declval<const It>())>>
		,require<std::is_constructible_v<bool, decltype(std::declval<const It>() >= std::declval<const CIt>())>>
		,require<std::is_constructible_v<bool, decltype(std::declval<const CIt>() >= std::declval<const It>())>>
		,require<std::is_same_v<decltype(std::declval<const It>() - std::declval<const CIt>()), iter::difference<It>>>
		,require<std::is_same_v<decltype(std::declval<const CIt>() - std::declval<const It>()), iter::difference<It>>>
	>> : std::true_type { };

template<class T
	,class = void>
struct is_container_helper : std::false_type { };

template<class T>
struct is_container_helper<T
	,std::void_t<void
		,typename T::value_type
		,typename T::reference
		,typename T::const_reference
		,typename T::iterator
		,typename T::const_iterator
		,typename T::difference_type
		,typename T::size_type
		,require<std::is_destructible_v<T>>
		,require<std::is_same_v<typename T::reference, cont::value<T>&>>
		,require<std::is_same_v<cont::creference<T>, const cont::value<T>&>>
		,require<std::is_same_v<iter::value<cont::iterator<T>>, cont::value<T>>>
		,require<std::is_same_v<iter::value<cont::citerator<T>>, cont::value<T>>>
		,require<is_forward_iterator_v<cont::iterator<T>>>
		,require<is_forward_iterator_v<cont::citerator<T>>>
		,require<std::is_convertible_v<cont::iterator<T>, cont::citerator<T>>>
		,require<std::is_signed_v<cont::difference<T>>>
		,require<std::is_same_v<cont::difference<T>, iter::difference<cont::iterator<T>>>>
		,require<std::is_same_v<cont::difference<T>, iter::difference<cont::citerator<T>>>>
		,require<std::is_unsigned_v<cont::size<T>>>
		,require<mtk::saturate_cast<cont::difference<T>>(std::numeric_limits<cont::size<T>>::max()) >= std::numeric_limits<cont::difference<T>>::max()>
		,require<std::is_default_constructible_v<T>>
		,require<std::is_copy_constructible_v<T>>
		,require<std::is_copy_assignable_v<T>>
		,require<std::is_same_v<decltype(std::declval<T&>() = std::declval<T&>()), T&>>
		,require<std::is_move_constructible_v<T>>
		,require<std::is_move_assignable_v<T>>
		,require<std::is_same_v<decltype(std::declval<T&>() = std::declval<T>()), T&>>
		,require<std::is_destructible_v<T>>
		,require<std::is_same_v<decltype(std::declval<T&>().begin()), cont::iterator<T>>>
		,require<std::is_same_v<decltype(std::declval<const T&>().begin()), cont::citerator<T>>>
		,require<std::is_same_v<decltype(std::declval<T&>().cbegin()), cont::citerator<T>>>
		,require<std::is_same_v<decltype(std::declval<T&>().end()), cont::iterator<T>>>
		,require<std::is_same_v<decltype(std::declval<const T&>().end()), cont::citerator<T>>>
		,require<std::is_same_v<decltype(std::declval<T&>().cend()), cont::citerator<T>>>
		,require<std::is_convertible_v<decltype(std::declval<const T&>() == std::declval<const T&>()), bool>>
		,require<std::is_convertible_v<decltype(std::declval<T&>() != std::declval<T&>()), bool>>
		,decltype(std::declval<T&>().swap(std::declval<T&>()))
		,decltype(swap(std::declval<T&>(), std::declval<T&>()))
		,require<std::is_same_v<decltype(std::declval<T&>().size()), cont::size<T>>>
		,require<std::is_same_v<decltype(std::declval<T&>().max_size()), cont::size<T>>>
		,require<std::is_convertible_v<decltype(std::declval<T&>().empty()), bool>>
		,require<is_fwd_iters_interchangable<cont::iterator<T>, cont::citerator<T>>::value>
		,require<!is_random_access_iterator_v<cont::iterator<T>> || is_ra_iters_interchangable<cont::iterator<T>, cont::citerator<T>>::value>
		,require<std::is_convertible_v<decltype(std::declval<const cont::value<T>>() == std::declval<const cont::value<T>>()), bool>>
	>> : std::true_type { };



template<class T
	,class = void>
struct is_reversible_container_helper : std::false_type { };

template<class T>
struct is_reversible_container_helper<T
	,std::void_t<void
		,require<is_container_helper<T>::value>
		,require<is_bidirectional_iterator_v<cont::iterator<T>>>
		,typename T::reverse_iterator
		,typename T::const_reverse_iterator
		,require<std::is_same_v<iter::value<cont::riterator<T>>, cont::value<T>>>
		,require<std::is_same_v<iter::value<cont::criterator<T>>, cont::value<T>>>
		,require<std::is_same_v<decltype(std::declval<T&>().rbegin()), cont::riterator<T>>>
		,require<std::is_same_v<decltype(std::declval<const T&>().rbegin()), cont::criterator<T>>>
		,require<std::is_same_v<decltype(std::declval<T&>().crbegin()), cont::criterator<T>>>
		,require<std::is_same_v<decltype(std::declval<T&>().rend()), cont::riterator<T>>>
		,require<std::is_same_v<decltype(std::declval<const T&>().rend()), cont::criterator<T>>>
		,require<std::is_same_v<decltype(std::declval<T&>().crend()), cont::criterator<T>>>
	>> : std::true_type { };



template<class T
	,class = void>
struct is_allocator_aware_container_helper : std::false_type { };

template<class T>
struct is_allocator_aware_container_helper<T
	,std::void_t<void
		,require<is_container_helper<T>::value>
		,typename T::allocator_type
		,require<is_allocator_v<cont::allocator<T>>>
		,require<std::is_same_v<alloc::value<cont::allocator<T>>, cont::value<T>>>
		,require<std::is_same_v<decltype(std::declval<T&>().get_allocator()), cont::allocator<T>>>
		,require<std::is_default_constructible_v<cont::allocator<T>>>
		,require<std::is_constructible_v<T, cont::allocator<T>>>
		,require<std::is_constructible_v<T, const T, cont::allocator<T>>>
		,require<std::is_constructible_v<T, T&&, cont::allocator<T>>>
	>> : std::true_type { };

} // namespace impl_core



//! @brief Trait to check if a given type conforms to the
//! Container named requirement.
//!
//! Provides the member constant value equal to true if conformant,
//! else false.
template<class T>
struct is_container :
	impl_core::is_container_helper<T> { };

//! @brief Trait to check if a given type conforms to the
//! ReversibleContainer named requirement.
//!
//! Provides the member constant value equal to true if conformant,
//! else false.
template<class T>
struct is_reversible_container :
	impl_core::is_reversible_container_helper<T> { };

//! @brief Trait to check if a given type conforms to the
//! AllocatorAwareContainer named requirement.
//!
//! Provides the member constant value equal to true if conformant,
//! else false.
template<class T>
struct is_allocator_aware_container :
	impl_core::is_allocator_aware_container_helper<T> { };



//! Shorthand for is_container::value.
template<class T>
inline constexpr
bool
is_container_v = is_container<T>::value;

//! Shorthand for is_reversible_container::value.
template<class T>
inline constexpr
bool
is_reversible_container_v = is_reversible_container<T>::value;

//! Shorthand for is_allocator_aware_container::value.
template<class T>
inline constexpr
bool
is_allocator_aware_container_v = is_allocator_aware_container<T>::value;

//! @}

} // namespace mtk

#endif
