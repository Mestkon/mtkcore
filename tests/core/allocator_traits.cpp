#include <catch.hpp>

#include <mtk/core/allocator_traits.hpp>

using namespace mtk;

#include <memory>
#include <vector>

using allc = std::allocator<int>;
using non_alloc = int;
using non_alloc2 = std::vector<allc>;

TEST_CASE("core/allocator_traits: alloc typedefs are correct", "[core]")
{
	REQUIRE((std::is_same_v<typename std::allocator_traits<allc>::value_type, alloc::value<allc>>));
	REQUIRE((std::is_same_v<typename std::allocator_traits<allc>::pointer, alloc::pointer<allc>>));
	REQUIRE((std::is_same_v<typename std::allocator_traits<allc>::const_pointer, alloc::cpointer<allc>>));
	REQUIRE((std::is_same_v<typename std::allocator_traits<allc>::void_pointer, alloc::vpointer<allc>>));
	REQUIRE((std::is_same_v<typename std::allocator_traits<allc>::const_void_pointer, alloc::cvpointer<allc>>));
	REQUIRE((std::is_same_v<typename std::allocator_traits<allc>::difference_type, alloc::difference<allc>>));
	REQUIRE((std::is_same_v<typename std::allocator_traits<allc>::size_type, alloc::size<allc>>));
	REQUIRE((std::is_same_v<typename std::allocator_traits<allc>::propagate_on_container_copy_assignment, alloc::propagate_on_copy_assign<allc>>));
	REQUIRE((std::is_same_v<typename std::allocator_traits<allc>::propagate_on_container_move_assignment, alloc::propagate_on_move_assign<allc>>));
	REQUIRE((std::is_same_v<typename std::allocator_traits<allc>::propagate_on_container_swap, alloc::propagate_on_swap<allc>>));
	REQUIRE((std::is_same_v<typename std::allocator_traits<allc>::is_always_equal, alloc::is_always_equal<allc>>));
	REQUIRE((std::is_same_v<typename std::allocator_traits<allc>::template rebind_alloc<float>, alloc::rebind<allc, float>>));
}

TEST_CASE("core/allocator_traits: is_allocator does the correct thing", "[core]")
{
	REQUIRE(is_allocator_v<allc>);
	REQUIRE(!is_allocator_v<non_alloc>);
	REQUIRE(!is_allocator_v<non_alloc2>);
}
