#include <catch.hpp>

#include <mtk/core/result.hpp>

#include <system_error>

template<class T>
using result = mtk::result<T, std::error_code>;

TEST_CASE("core/result: Result is in expected state when given an error", "[core]")
{
	result<int> r = std::make_error_code(std::errc::bad_file_descriptor);

	REQUIRE(!r);
	REQUIRE(!r.has_value());

	REQUIRE(r.error() == std::errc::bad_file_descriptor);
}

TEST_CASE("core/result: Throws bad_result_access when accessing unengaged result using value()", "[core]")
{
	result<int> r = std::error_code();

	REQUIRE_THROWS_AS(r.value(), mtk::bad_result_access);
}

TEST_CASE("core/result: Result is in expected state when given a value", "[core]")
{
	result<int> r = 42;

	REQUIRE(r);
	REQUIRE(r.has_value());
	REQUIRE(*r == 42);
	REQUIRE(r.value() == 42);
}

TEST_CASE("core/result: Result value_or() returns default value when not engaged", "[core]")
{
	result<int> r = std::error_code();

	REQUIRE(r.value_or(69) == 69);
}

TEST_CASE("core/result: Result value_or() returns current value when engaged", "[core]")
{
	result<int> r = 420;

	REQUIRE(r.value_or(69) == 420);
}
