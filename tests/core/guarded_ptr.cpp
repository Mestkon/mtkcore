#include <catch.hpp>

#include <mtk/core/guarded_ptr.hpp>

using namespace mtk;

TEST_CASE("core/guarded_ptr: default constructor initializes to nullptr", "[core]")
{
	guarded_ptr<int> ptr;
	REQUIRE(static_cast<int*>(ptr) == nullptr);
	REQUIRE(!ptr);
}

TEST_CASE("core/guarded_ptr: pointer constructor initializes to given pointer", "[core]")
{
	guarded_ptr<int> ptr_null(nullptr);
	REQUIRE(static_cast<int*>(ptr_null) == nullptr);
	REQUIRE(!ptr_null);

	int i = 0;
	guarded_ptr<int> ptr_int(&i);
	REQUIRE(static_cast<int*>(ptr_int) == &i);
	REQUIRE(ptr_int);
}

TEST_CASE("core/guarded_ptr: assignment rebinds the pointer", "[core]")
{
	guarded_ptr<int> ptr;
	REQUIRE(!ptr);

	int i = 0;
	ptr = &i;
	REQUIRE(static_cast<int*>(ptr) == &i);
	REQUIRE(ptr);
}

TEST_CASE("core/guarded_ptr: dereference nullptr throws exception", "[core]")
{
	guarded_ptr<int> ptr;
	REQUIRE(!ptr);

	REQUIRE_THROWS_AS(*ptr, nullptr_exception);
	REQUIRE_THROWS_AS(ptr.operator->(), nullptr_exception);
}

TEST_CASE("core/guarded_ptr: dereference valid ptr returns correct value", "[core]")
{
	int i1 = 42;
	guarded_ptr<int> ptr1(&i1);
	REQUIRE(*ptr1 == 42);
	REQUIRE(ptr1.operator->() == &i1);

	float f2 = 69.0f;
	guarded_ptr<float> ptr2(&f2);
	REQUIRE(*ptr2 == 69.0f);
	REQUIRE(ptr2.operator->() == &f2);
}

