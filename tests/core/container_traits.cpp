#include <catch.hpp>

#include <mtk/core/container_traits.hpp>

using namespace mtk;

#include <array>
#include <forward_list>
#include <map>
#include <vector>

using c_arr = int[10];
using arr = std::array<llong, 4>;
using flist = std::forward_list<float>;
using map = std::map<size_t, char>;
using vec = std::vector<std::nullptr_t>;
using not_cont = int;

TEST_CASE("core/container_traits: container_traits has correct typedefs")
{
	using carr_trait = container_traits<c_arr>;
	REQUIRE((std::is_same_v<typename carr_trait::value_type, int>));
	REQUIRE((std::is_same_v<typename carr_trait::reference, int&>));
	REQUIRE((std::is_same_v<typename carr_trait::const_reference, const int&>));
	REQUIRE((std::is_same_v<typename carr_trait::pointer, int*>));
	REQUIRE((std::is_same_v<typename carr_trait::const_pointer, const int*>));
	REQUIRE((std::is_same_v<typename carr_trait::iterator, int*>));
	REQUIRE((std::is_same_v<typename carr_trait::const_iterator, const int*>));
	REQUIRE((std::is_same_v<typename carr_trait::size_type, size_t>));
	REQUIRE((std::is_same_v<typename carr_trait::difference_type, ptrdiff_t>));
	REQUIRE((std::is_same_v<typename carr_trait::reverse_iterator, std::reverse_iterator<int*>>));
	REQUIRE((std::is_same_v<typename carr_trait::const_reverse_iterator, std::reverse_iterator<const int*>>));

	using vec_trait = container_traits<vec>;
	REQUIRE((std::is_same_v<typename vec_trait::value_type, typename vec::value_type>));
	REQUIRE((std::is_same_v<typename vec_trait::reference, typename vec::reference>));
	REQUIRE((std::is_same_v<typename vec_trait::const_reference, typename vec::const_reference>));
	REQUIRE((std::is_same_v<typename vec_trait::pointer, typename vec::pointer>));
	REQUIRE((std::is_same_v<typename vec_trait::const_pointer, typename vec::const_pointer>));
	REQUIRE((std::is_same_v<typename vec_trait::iterator, typename vec::iterator>));
	REQUIRE((std::is_same_v<typename vec_trait::const_iterator, typename vec::const_iterator>));
	REQUIRE((std::is_same_v<typename vec_trait::size_type, typename vec::size_type>));
	REQUIRE((std::is_same_v<typename vec_trait::difference_type, typename vec::difference_type>));
	REQUIRE((std::is_same_v<typename vec_trait::reverse_iterator, typename vec::reverse_iterator>));
	REQUIRE((std::is_same_v<typename vec_trait::const_reverse_iterator, typename vec::const_reverse_iterator>));
	REQUIRE((std::is_same_v<typename vec_trait::allocator_type, typename vec::allocator_type>));
}

TEST_CASE("core/container_traits: cont typedefs are correct", "[core]")
{
	using vec_trait = container_traits<vec>;
	REQUIRE((std::is_same_v<typename vec_trait::value_type, cont::value<vec>>));
	REQUIRE((std::is_same_v<typename vec_trait::reference, cont::reference<vec>>));
	REQUIRE((std::is_same_v<typename vec_trait::const_reference, cont::creference<vec>>));
	REQUIRE((std::is_same_v<typename vec_trait::pointer, cont::pointer<vec>>));
	REQUIRE((std::is_same_v<typename vec_trait::const_pointer, cont::cpointer<vec>>));
	REQUIRE((std::is_same_v<typename vec_trait::iterator, cont::iterator<vec>>));
	REQUIRE((std::is_same_v<typename vec_trait::const_iterator, cont::citerator<vec>>));
	REQUIRE((std::is_same_v<typename vec_trait::size_type, cont::size<vec>>));
	REQUIRE((std::is_same_v<typename vec_trait::difference_type, cont::difference<vec>>));
	REQUIRE((std::is_same_v<typename vec_trait::reverse_iterator, cont::riterator<vec>>));
	REQUIRE((std::is_same_v<typename vec_trait::const_reverse_iterator, cont::criterator<vec>>));
	REQUIRE((std::is_same_v<typename vec_trait::allocator_type, cont::allocator<vec>>));

	using map_trait = container_traits<map>;
	REQUIRE((std::is_same_v<typename map_trait::value_type, cont::value<map>>));
	REQUIRE((std::is_same_v<typename map_trait::reference, cont::reference<map>>));
	REQUIRE((std::is_same_v<typename map_trait::const_reference, cont::creference<map>>));
	REQUIRE((std::is_same_v<typename map_trait::pointer, cont::pointer<map>>));
	REQUIRE((std::is_same_v<typename map_trait::const_pointer, cont::cpointer<map>>));
	REQUIRE((std::is_same_v<typename map_trait::iterator, cont::iterator<map>>));
	REQUIRE((std::is_same_v<typename map_trait::const_iterator, cont::citerator<map>>));
	REQUIRE((std::is_same_v<typename map_trait::size_type, cont::size<map>>));
	REQUIRE((std::is_same_v<typename map_trait::difference_type, cont::difference<map>>));
	REQUIRE((std::is_same_v<typename map_trait::reverse_iterator, cont::riterator<map>>));
	REQUIRE((std::is_same_v<typename map_trait::const_reverse_iterator, cont::criterator<map>>));
	REQUIRE((std::is_same_v<typename map_trait::allocator_type, cont::allocator<map>>));
}

TEST_CASE("core/container_traits: is_container does the correct thing", "[core]")
{
	REQUIRE(!is_container_v<c_arr>);
	REQUIRE(is_container_v<arr>);
	REQUIRE(!is_container_v<flist>); //std::forward_list does not implement the .size() requirement of a container.
	REQUIRE(is_container_v<map>);
	REQUIRE(is_container_v<vec>);
	REQUIRE(!is_container_v<not_cont>);
}

TEST_CASE("core/container_traits: is_reversible_container does the correct thing", "[core]")
{
	REQUIRE(!is_reversible_container_v<c_arr>);
	REQUIRE(is_reversible_container_v<arr>);
	REQUIRE(!is_reversible_container_v<flist>);
	REQUIRE(is_reversible_container_v<map>);
	REQUIRE(is_reversible_container_v<vec>);
	REQUIRE(!is_reversible_container_v<not_cont>);
}

TEST_CASE("core/container_traits: is_allocator_aware_container does the correct thing", "[core]")
{
	REQUIRE(!is_allocator_aware_container_v<c_arr>);
	REQUIRE(!is_allocator_aware_container_v<arr>);
	REQUIRE(!is_allocator_aware_container_v<flist>);
	REQUIRE(is_allocator_aware_container_v<map>);
	REQUIRE(is_allocator_aware_container_v<vec>);
	REQUIRE(!is_allocator_aware_container_v<not_cont>);
}
