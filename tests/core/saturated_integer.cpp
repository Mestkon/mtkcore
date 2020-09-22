#include <catch.hpp>

#include <mtk/core/saturated_integer.hpp>

#include <climits>

using namespace mtk::types;

namespace mtk {
template<class T>
std::ostream&
operator<<(std::ostream& os, saturated_integer<T> t)
{
	os << t.value();
}
}

#ifdef MTK_FIXED_WIDTH_INTS
TEST_CASE("core/types: Fixed width saturated ints correct size", "[core]")
{
	REQUIRE(sizeof(int8_sat)*CHAR_BIT == 8u);
	REQUIRE(sizeof(int16_sat)*CHAR_BIT == 16u);
	REQUIRE(sizeof(int32_sat)*CHAR_BIT == 32u);

	REQUIRE(sizeof(uint8_sat)*CHAR_BIT == 8u);
	REQUIRE(sizeof(uint16_sat)*CHAR_BIT == 16u);
	REQUIRE(sizeof(uint32_sat)*CHAR_BIT == 32u);
}
#endif

TEST_CASE("core/saturated_integer: all tests", "[core]")
{
	int32_sat v1 = 70;
	int32_sat v2 = -400;
	uint16_sat v3 = 27;
	uint16_sat v4 = 69;

	int32_sat v_imax = std::numeric_limits<int32_sat>::max();
	int32_sat v_imin = std::numeric_limits<int32_sat>::min();
	uint16_sat v_umax = std::numeric_limits<uint16_sat>::max();

	auto cp1 = v1;
	auto cp2 = v2;
	auto cp3 = v3;
	auto cp4 = v4;

	auto cp_imax = v_imax;
	auto cp_imin = v_imin;
	auto cp_umax = v_umax;

	SECTION("core/saturated_integer: Constructors initializes correctly", "[core]")
	{
		REQUIRE(v1.value() == 70);
		REQUIRE(v2.value() == -400);
		REQUIRE(v3.value() == 27u);
		REQUIRE(v4.value() == 69u);

		REQUIRE(v_imax.value() == std::numeric_limits<int32>::max());
		REQUIRE(v_imin.value() == std::numeric_limits<int32>::min());
		REQUIRE(v_umax.value() == std::numeric_limits<uint16>::max());

		REQUIRE(static_cast<int32>(v1) == 70);
		REQUIRE(static_cast<int32>(v2) == -400);
		REQUIRE(static_cast<uint16>(v3) == 27u);
		REQUIRE(static_cast<uint16>(v4) == 69u);

		REQUIRE(static_cast<int32>(v_imax) == std::numeric_limits<int32>::max());
		REQUIRE(static_cast<int32>(v_imin) == std::numeric_limits<int32>::min());
		REQUIRE(static_cast<uint16>(v_umax) == std::numeric_limits<uint16>::max());
	}

	SECTION("core/saturated_integer: Comparisons work as expected", "[core]")
	{
		REQUIRE(v1 == cp1);
		REQUIRE(v2 != cp1);
		REQUIRE(v4 == cp4);
		REQUIRE(v3 != cp4);

		REQUIRE(v2 < v1);
		REQUIRE(v3 < v4);
		REQUIRE(v2 <= v2);
		REQUIRE(v2 <= cp1);
		REQUIRE(cp1 > cp2);
		REQUIRE(cp4 > cp3);
		REQUIRE(v4 >= v4);
		REQUIRE(v4 >= cp3);
	}

	SECTION("core/saturated_integer: Unary operators work as expected", "[core]")
	{
		REQUIRE(cp1++ == v1);
		REQUIRE(cp1 == v1.value() + 1);

		REQUIRE(++cp3 == v3.value() + 1);

		REQUIRE(cp1-- == v1.value() + 1);
		REQUIRE(cp1 == v1);

		REQUIRE(--cp3 == v3);

		REQUIRE(+cp2 == v2);
		REQUIRE(cp2 == v2);
		REQUIRE(+cp3 == v3);
		REQUIRE(cp3 == v3);

		REQUIRE(-cp1 == -70);
		REQUIRE(cp1 == v1);
		REQUIRE(-cp4 == 0u);
		REQUIRE(cp4 == v4);

		REQUIRE(++cp_imax == v_imax);
		REQUIRE(--cp_imin == v_imin);
		REQUIRE(++cp_umax == v_umax);
	}

	SECTION("core/saturated_integer: Binary additative operators work as expected", "[core]")
	{
		REQUIRE(cp1 + cp2 == -330);
		REQUIRE(cp3 + cp4 == 96u);
		REQUIRE(cp1 + cp_imax == v_imax);
		REQUIRE(cp3 + cp_umax == v_umax);
		REQUIRE(cp1 + 3 == 73);
		REQUIRE(27 + cp2 == -373);

		REQUIRE(cp1 - cp2 == 470);
		REQUIRE(cp4 - cp3 == 42u);
		REQUIRE(cp2 - cp_imax == v_imin);
		REQUIRE(cp3 - cp_umax == 0u);
		REQUIRE(cp4 - 1 == 68u);

		REQUIRE((cp1 += cp2) == -330);
		REQUIRE((cp3 += cp4) == 96u);

		REQUIRE((cp1 -= cp2) == v1);
		REQUIRE((cp3 -= cp4) == v3);
	}

	SECTION("core/saturated_integer: Binary multiplicative operators work as expected", "[core]")
	{
		REQUIRE(cp1 * cp1 == 70*70);
		REQUIRE(cp2 * 2 == -800);
		REQUIRE(10 * cp3 == 270u);
		REQUIRE(cp4 * cp3 == 27u*69u);

		REQUIRE(cp2 / cp1 == -400 / 70);
		REQUIRE(cp2 / 2 == -200);
		REQUIRE(cp3 / 3 == 9u);

		REQUIRE((cp1 *= cp2) == -400*70);
		REQUIRE((cp2 *= 3) == -1200);

		REQUIRE((cp3 /= 3) == 9u);
		REQUIRE((cp4 /= cp3) == 7u);
	}
}
