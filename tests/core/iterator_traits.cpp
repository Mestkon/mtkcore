#include <catch.hpp>

#include <mtk/core/iterator_traits.hpp>

using namespace mtk;

#include <array>
#include <forward_list>
#include <map>
#include <vector>

using c_arr_it = decltype(std::begin(std::declval<int(&)[10]>()));
using arr_it = decltype(std::declval<std::array<llong, 4>&>().begin());
using flist_it = decltype(std::declval<std::forward_list<float>&>().begin());
using map_it = decltype(std::declval<std::map<size_t, char>&>().begin());
using vec_it = decltype(std::declval<std::vector<std::nullptr_t>&>().begin());
using non_it = int;

struct vector_sentinel
{
};

bool operator==(vector_sentinel, vec_it) { return true; }
bool operator==(vec_it, vector_sentinel) { return true; }
bool operator!=(vector_sentinel, vec_it) { return false; }
bool operator!=(vec_it, vector_sentinel) { return false; }


template<class It>
void iter_test_function()
{
	REQUIRE((std::is_same_v<typename std::iterator_traits<It>::value_type, iter::value<It>>));
	REQUIRE((std::is_same_v<typename std::iterator_traits<It>::difference_type, iter::difference<It>>));
	REQUIRE((std::is_same_v<typename std::iterator_traits<It>::reference, iter::reference<It>>));
	REQUIRE((std::is_same_v<typename std::iterator_traits<It>::pointer, iter::pointer<It>>));
	REQUIRE((std::is_same_v<typename std::iterator_traits<It>::iterator_category, iter::category<It>>));
}

TEST_CASE("core/iterator_traits: iter typedefs are correct", "[core]")
{
	iter_test_function<c_arr_it>();
	iter_test_function<arr_it>();
	iter_test_function<flist_it>();
	iter_test_function<map_it>();
	iter_test_function<vec_it>();
}

TEST_CASE("core/iterator_traits: is_iterator does the correct thing", "[core]")
{
	REQUIRE(is_iterator_v<c_arr_it>);
	REQUIRE(is_iterator_v<arr_it>);
	REQUIRE(is_iterator_v<flist_it>);
	REQUIRE(is_iterator_v<map_it>);
	REQUIRE(is_iterator_v<vec_it>);
	REQUIRE(!is_iterator_v<non_it>);
}

TEST_CASE("core/iterator_traits: is_input_iterator does the correct thing", "[core]")
{
	REQUIRE(is_input_iterator_v<c_arr_it>);
	REQUIRE(is_input_iterator_v<arr_it>);
	REQUIRE(is_input_iterator_v<flist_it>);
	REQUIRE(is_input_iterator_v<map_it>);
	REQUIRE(is_input_iterator_v<vec_it>);
	REQUIRE(!is_input_iterator_v<non_it>);
}

TEST_CASE("core/iterator_traits: is_output_iterator does the correct thing", "[core]")
{
	REQUIRE((is_output_iterator_v<c_arr_it, int>));
	REQUIRE((is_output_iterator_v<arr_it, llong>));
	REQUIRE((is_output_iterator_v<flist_it, float>));
	REQUIRE(!(is_output_iterator_v<map_it, std::pair<size_t, char>>));
	REQUIRE((is_output_iterator_v<vec_it, std::nullptr_t>));
	REQUIRE(!(is_output_iterator_v<non_it, bool>));
}

TEST_CASE("core/iterator_traits: is_forward_iterator does the correct thing", "[core]")
{
	REQUIRE(is_forward_iterator_v<c_arr_it>);
	REQUIRE(is_forward_iterator_v<arr_it>);
	REQUIRE(is_forward_iterator_v<flist_it>);
	REQUIRE(is_forward_iterator_v<map_it>);
	REQUIRE(is_forward_iterator_v<vec_it>);
	REQUIRE(!is_forward_iterator_v<non_it>);
}

TEST_CASE("core/iterator_traits: is_bidirectional_iterator does the correct thing", "[core]")
{
	REQUIRE(is_bidirectional_iterator_v<c_arr_it>);
	REQUIRE(is_bidirectional_iterator_v<arr_it>);
	REQUIRE(!is_bidirectional_iterator_v<flist_it>);
	REQUIRE(is_bidirectional_iterator_v<map_it>);
	REQUIRE(is_bidirectional_iterator_v<vec_it>);
	REQUIRE(!is_bidirectional_iterator_v<non_it>);
}

TEST_CASE("core/iterator_traits: is_random_access_iterator does the correct thing", "[core]")
{
	REQUIRE(is_random_access_iterator_v<c_arr_it>);
	REQUIRE(is_random_access_iterator_v<arr_it>);
	REQUIRE(!is_random_access_iterator_v<flist_it>);
	REQUIRE(!is_random_access_iterator_v<map_it>);
	REQUIRE(is_random_access_iterator_v<vec_it>);
	REQUIRE(!is_random_access_iterator_v<non_it>);
}

TEST_CASE("core/iterator_traits: is_sentinel_for does the correct thing", "[core]")
{
	REQUIRE((is_sentinel_for_v<c_arr_it, c_arr_it>));
	REQUIRE((is_sentinel_for_v<arr_it, arr_it>));
	REQUIRE((is_sentinel_for_v<flist_it, flist_it>));
	REQUIRE((is_sentinel_for_v<map_it, map_it>));
	REQUIRE((is_sentinel_for_v<vec_it, vec_it>));
	REQUIRE(!(is_sentinel_for_v<non_it, non_it>));
	REQUIRE((is_sentinel_for_v<vector_sentinel, vec_it>));
}
