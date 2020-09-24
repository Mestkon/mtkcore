#include <catch.hpp>

#include <mtk/core/scope_guard.hpp>

using namespace mtk;

TEST_CASE("core/scope_guard: scope_guard always does the thing", "[core]")
{
	int i = 0;

	{
		scope_guard s = [&i]() {
			i = 42;
		};
	}
	REQUIRE(i == 42);

	try {
		scope_guard s = [&i]() {
			i = 69;
		};
		throw 1;
	} catch (...) { }
	REQUIRE(i == 69);
}

TEST_CASE("core/scope_guard: scope_guard doesn't do the thing when released", "[core]")
{
	int i = 0;

	{
		scope_guard s = [&i]() {
			i = 42;
		};
		s.release();
	}
	REQUIRE(i == 0);

	try {
		scope_guard s = [&i]() {
			i = 69;
		};
		s.release();
		throw 1;
	} catch (...) { }
	REQUIRE(i == 0);
}

TEST_CASE("core/scope_guard: scope_success does the thing when no exception", "[core]")
{
	int i = 0;

	{
		scope_success s = [&i]() {
			i = 42;
		};
	}
	REQUIRE(i == 42);

	try {
		scope_success s = [&i]() {
			i = 69;
		};
		throw 1;
	} catch (...) { }
	REQUIRE(i == 42);
}

TEST_CASE("core/scope_guard: scope_success doesn't do the thing when released", "[core]")
{
	int i = 0;

	{
		scope_success s = [&i]() {
			i = 42;
		};
		s.release();
	}
	REQUIRE(i == 0);

	try {
		scope_success s = [&i]() {
			i = 69;
		};
		s.release();
		throw 1;
	} catch (...) { }
	REQUIRE(i == 0);
}

TEST_CASE("core/scope_guard: scope_failure does the thing when exception", "[core]")
{
	int i = 0;

	{
		scope_failure s = [&i]() {
			i = 42;
		};
	}
	REQUIRE(i == 0);

	try {
		scope_failure s = [&i]() {
			i = 69;
		};
		throw 1;
	} catch (...) { }
	REQUIRE(i == 69);
}

TEST_CASE("core/scope_guard: scope_failure doesn't do the thing when released", "[core]")
{
	int i = 0;

	{
		scope_failure s = [&i]() {
			i = 42;
		};
		s.release();
	}
	REQUIRE(i == 0);

	try {
		scope_failure s = [&i]() {
			i = 69;
		};
		s.release();
		throw 1;
	} catch (...) { }
	REQUIRE(i == 0);
}


