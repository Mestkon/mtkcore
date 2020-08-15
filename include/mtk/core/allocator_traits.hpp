#ifndef MTK_CORE_ALLOCATOR_TRAITS_HPP
#define MTK_CORE_ALLOCATOR_TRAITS_HPP

//! @file
//! Contains type traits for allocators.

#include <mtk/core/types.hpp>

#include <memory>
#include <utility>

namespace mtk {

//! @defgroup allocator_traits mtk/core/allocator_traits.hpp
//! @{

//! Namespace to shorten std::allocator_traits
namespace alloc {

//! @addtogroup allocator_traits
//! @{

//! Shorthand for std::allocator_traits::value_type.
template<class T>
using value = typename std::allocator_traits<T>::value_type;
//! Shorthand for std::allocator_traits::pointer.
template<class T>
using pointer = typename std::allocator_traits<T>::pointer;
//! Shorthand for std::allocator_traits::const_pointer.
template<class T>
using cpointer = typename std::allocator_traits<T>::const_pointer;
//! Shorthand for std::allocator_traits::void_pointer.
template<class T>
using vpointer = typename std::allocator_traits<T>::void_pointer;
//! Shorthand for std::allocator_traits::const_void_pointer.
template<class T>
using cvpointer = typename std::allocator_traits<T>::const_void_pointer;
//! Shorthand for std::allocator_traits::difference_type.
template<class T>
using difference = typename std::allocator_traits<T>::difference_type;
//! Shorthand for std::allocator_traits::size_type.
template<class T>
using size = typename std::allocator_traits<T>::size_type;

//! Shorthand for std::allocator_traits::propagate_on_container_copy_assignment.
template<class T>
inline constexpr
auto
propagate_copy = std::allocator_traits<T>::propagate_on_container_copy_assignment;
//! Shorthand for std::allocator_traits::propagate_on_container_move_assignment.
template<class T>
inline constexpr
auto
propagate_move = std::allocator_traits<T>::propagate_on_container_move_assignment;
//! Shorthand for std::allocator_traits::propagate_on_container_swap.
template<class T>
inline constexpr
auto
propagate_swap = std::allocator_traits<T>::propagate_on_container_swap;
//! Shorthand for std::allocator_traits::is_always_equal.
template<class T>
inline constexpr
auto
is_always_equal = std::allocator_traits<T>::is_always_equal;

//! Shorthand for std::allocator_traits::rebind_alloc.
template<class Alloc
	,class T>
using rebind = typename std::allocator_traits<Alloc>::template rebind_alloc<T>;

//! Shorthand for std::allocator_traits::allocate.
template<class Alloc>
[[nodiscard]]
pointer<Alloc>
allocate(Alloc& a, size<Alloc> n)
{
	return std::allocator_traits<Alloc>::allocate(a, n);
}

//! Shorthand for std::allocator_traits::allocate.
template<class Alloc>
[[nodiscard]]
pointer<Alloc>
allocate(Alloc& a, size<Alloc> n, cvpointer<Alloc> hint)
{
	return std::allocator_traits<Alloc>::allocate(a, n, hint);
}

//! Shorthand for std::allocator_traits::deallocate.
template<class Alloc>
void
deallocate(Alloc& a, pointer<Alloc> p, size<Alloc> n)
{
	std::allocator_traits<Alloc>::deallocate(a, p, n);
}

//! Shorthand for std::allocator_traits::construct.
template<class Alloc
	,class T
	,class... Args>
void
construct(Alloc& a, T* p, Args&& ...args)
{
	std::allocator_traits<Alloc>::construct(a, p, std::forward<Args>(args)...);
}

//! Shorthand for std::allocator_traits::destroy.
template<class Alloc
	,class T>
void
destroy(Alloc& a, T* p)
{
	std::allocator_traits<Alloc>::destroy(a, p);
}

//! Shorthand for std::allocator_traits::max_size.
template<class Alloc>
size<Alloc>
max_size(const Alloc& a) noexcept
{
	return std::allocator_traits<Alloc>::max_size(a);
}

//! Shorthand for std::allocator_traits::select_on_container_copy_construction.
template<class Alloc>
Alloc
select_copy(const Alloc& a)
{
	return std::allocator_traits<Alloc>::select_on_container_copy_construction(a);
}

//! @}

} // namespace alloc



namespace impl_core {

template<class T
	,class = void>
struct is_allocator_helper : std::false_type { };

template<class T>
struct is_allocator_helper<T
	,std::void_t<void
		,typename T::value_type
		,require<std::is_same_v<decltype(std::declval<T&>().allocate(std::declval<alloc::size<T>>())), alloc::pointer<T>>>
		,decltype(std::declval<T&>().deallocate(std::declval<alloc::pointer<T>>(), std::declval<alloc::size<T>>()))
		,require<std::is_same_v<decltype(std::declval<const T>() == std::declval<const T>()), bool>>
		,require<std::is_same_v<decltype(std::declval<const T>() != std::declval<const T>()), bool>>
		,require<std::is_nothrow_copy_constructible_v<T>>
		,require<std::is_nothrow_copy_assignable_v<T>>
		,require<std::is_nothrow_constructible_v<T, alloc::rebind<T, std::nullptr_t>>>
		,require<std::is_nothrow_move_constructible_v<T>>
		,require<std::is_nothrow_move_assignable_v<T>>
		,require<std::is_nothrow_constructible_v<T, alloc::rebind<T, std::nullptr_t>&&>>
	>> : std::true_type { };

} // namespace impl_core



//! @brief Trait to check if a given type conforms to the
//! Allocator named requirement.
//!
//! Provides the member constant value equal to true if conformant,
//! else false.
template<class T>
struct is_allocator
#ifndef MTK_DOXYGEN
	:impl_core::is_allocator_helper<T>
#endif
{ };

//! Shorthand for is_allocator::value.
template<class T>
inline constexpr
bool
is_allocator_v = is_allocator<T>::value;

//! @}

} // namespace mtk

#endif
