#include <catch.hpp>

#include <mtk/core/types.hpp>

#include <climits>

using namespace mtk;

#define REQ_INT 0
#define REQ_FLT 1
#define REQ_OTH 2

template<class T,
	require<std::is_integral_v<T>> = 0>
static
int
test_require(T)
{
	return REQ_INT;
}

template<class T,
	require<std::is_floating_point_v<T>> = 0>
static
int
test_require(T)
{
	return REQ_FLT;
}

template<class T,
	require<!std::is_integral_v<T> && !std::is_floating_point_v<T>> = 0>
static
int
test_require(T)
{
	return REQ_OTH;
}


TEST_CASE("core/types: Fixed width ints correct size", "[core]")
{
#ifdef MTK_FIXED_WIDTH_INTS
	REQUIRE(sizeof(int8)*CHAR_BIT == 8u);
	REQUIRE(sizeof(int16)*CHAR_BIT == 16u);
	REQUIRE(sizeof(int32)*CHAR_BIT == 32u);
	REQUIRE(sizeof(int64)*CHAR_BIT == 64u);

	REQUIRE(sizeof(uint8)*CHAR_BIT == 8u);
	REQUIRE(sizeof(uint16)*CHAR_BIT == 16u);
	REQUIRE(sizeof(uint32)*CHAR_BIT == 32u);
	REQUIRE(sizeof(uint64)*CHAR_BIT == 64u);
#endif
}

TEST_CASE("core/types: Require based template selection", "[core]")
{
	REQUIRE(test_require(0) == REQ_INT);
	REQUIRE(test_require(0.0f) == REQ_FLT);
	REQUIRE(test_require(nullptr) == REQ_OTH);
}

