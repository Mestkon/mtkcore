#include <catch.hpp>

#include <mtk/core/flag_operators.hpp>

enum class test_enum
{
	f0 = 0,
	f1 = (1 << 0),
	f2 = (1 << 1),
	f1_or_f2 = (f1 | f2),
	f3 = (1 << 2),
	f1_or_f3 = (f1 | f3),
	f1_or_f2_or_f3 = (f1 | f2 | f3),
	f2_or_f3 = (f2 | f3),
	f4 = (1 << 3),
	f1_or_f4 = (f1 | f4),
	f1_or_f2_or_f4 = (f1 | f2 | f4),
	f1_or_f3_or_f4 = (f1 | f3 | f4),

	not_f3 = ~f3,
	not_f2_and_not_f3 = ~(f2 | f3)

};
MTK_DEFINE_FLAG_OPERATORS(test_enum)

template<class T>
inline constexpr auto is_test_enum = std::is_same_v<T, test_enum>;

TEST_CASE("core/flag_operators: oring flags together does the correct thing", "[core]")
{
	auto f1_or_f2 = test_enum::f1 | test_enum::f2;
	REQUIRE(is_test_enum<decltype(f1_or_f2)>);
	REQUIRE(f1_or_f2 == test_enum::f1_or_f2);

	auto f1_or_f2_or_f4 = f1_or_f2 | test_enum::f4;
	REQUIRE(f1_or_f2_or_f4 == test_enum::f1_or_f2_or_f4);

	auto f1_or_f3 = test_enum::f1;
	f1_or_f3 |= test_enum::f3;
	REQUIRE(f1_or_f3 == test_enum::f1_or_f3);

	auto f1_or_f3_or_f4 = test_enum::f1_or_f3;
	f1_or_f3_or_f4 |= test_enum::f4;
	REQUIRE(f1_or_f3_or_f4 == test_enum::f1_or_f3_or_f4);
}

TEST_CASE("core/flag_operators: anding flags together does the correct thing", "[core]")
{
	auto f1 = test_enum::f1_or_f2 & test_enum::f1;
	REQUIRE(is_test_enum<decltype(f1)>);
	REQUIRE(f1 == test_enum::f1);

	auto f0 = test_enum::f1_or_f2_or_f4 & test_enum::f3;
	REQUIRE(f0 == test_enum::f0);

	auto f1_or_f2 = test_enum::f1_or_f2_or_f4 & test_enum::f1_or_f2;
	REQUIRE(f1_or_f2 == test_enum::f1_or_f2);

	auto f3 = test_enum::f1_or_f3;
	f3 &= test_enum::f3;
	REQUIRE(f3 == test_enum::f3);

	auto f1_or_f4 = test_enum::f1_or_f3_or_f4;
	f1_or_f4 &= test_enum::f1_or_f4;
	REQUIRE(f1_or_f4 == test_enum::f1_or_f4);
}

TEST_CASE("core/flag_operators: xoring flags together does the correct thing", "[core]")
{
	auto f1_or_f2 = test_enum::f1 ^ test_enum::f2;
	REQUIRE(is_test_enum<decltype(f1_or_f2)>);
	REQUIRE(f1_or_f2 == test_enum::f1_or_f2);

	auto f1_or_f2_or_f4 = f1_or_f2 ^ test_enum::f4;
	REQUIRE(f1_or_f2_or_f4 == test_enum::f1_or_f2_or_f4);

	auto f1_or_f4 = test_enum::f1_or_f2_or_f4 ^ test_enum::f2;
	REQUIRE(f1_or_f4 == test_enum::f1_or_f4);

	auto f1_or_f3 = test_enum::f1;
	f1_or_f3 ^= test_enum::f3;
	REQUIRE(f1_or_f3 == test_enum::f1_or_f3);

	auto f1_or_f3_or_f4 = test_enum::f1_or_f3;
	f1_or_f3_or_f4 ^= test_enum::f4;
	REQUIRE(f1_or_f3_or_f4 == test_enum::f1_or_f3_or_f4);

	auto f1 = test_enum::f1_or_f2_or_f3;
	f1 ^= test_enum::f2_or_f3;
	REQUIRE(f1 == test_enum::f1);
}

TEST_CASE("core/flag_operators: noting flags does the correct thing", "[core]")
{
	auto not_f3 = ~test_enum::f3;
	REQUIRE(is_test_enum<decltype(not_f3)>);
	REQUIRE(not_f3 == test_enum::not_f3);

	auto not_f2_and_not_f3 = ~test_enum::f2_or_f3;
	REQUIRE(not_f2_and_not_f3 == test_enum::not_f2_and_not_f3);
}
