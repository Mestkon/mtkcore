#include <catch.hpp>

#include <mtk/core/casts.hpp>

using namespace mtk;

void overload() { }
void overload(int) { }
int overload(std::nullptr_t) { return 0; }
int overload(float) { return 0; }

struct test
{
	void overload() { }
	void overload(int) { }
	int overload(std::nullptr_t) { return 0; }

	void overload(int) const { }
	int overload(float) const { return 0; }
};

TEST_CASE("core/casts: byte_cast return type qualifier equal to input", "[core]")
{
	int my_int = 0;

	int* int_ptr = &my_int;
	byte* as_byte = reinterpret_cast<byte*>(int_ptr);
	auto from_byte_cast = byte_cast(int_ptr);

	REQUIRE(from_byte_cast == as_byte);
	REQUIRE(!std::is_const_v<std::remove_pointer_t<decltype(from_byte_cast)>>);
	REQUIRE(!std::is_volatile_v<std::remove_pointer_t<decltype(from_byte_cast)>>);

	const int* c_int_ptr = &my_int;
	const byte* c_as_byte = reinterpret_cast<const byte*>(c_int_ptr);
	auto c_from_byte_cast = byte_cast(c_int_ptr);

	REQUIRE(c_from_byte_cast == c_as_byte);
	REQUIRE(std::is_const_v<std::remove_pointer_t<decltype(c_from_byte_cast)>>);
	REQUIRE(!std::is_volatile_v<std::remove_pointer_t<decltype(c_from_byte_cast)>>);

	volatile int* v_int_ptr = &my_int;
	volatile byte* v_as_byte = reinterpret_cast<volatile byte*>(v_int_ptr);
	auto v_from_byte_cast = byte_cast(v_int_ptr);

	REQUIRE(v_from_byte_cast == v_as_byte);
	REQUIRE(!std::is_const_v<std::remove_pointer_t<decltype(v_from_byte_cast)>>);
	REQUIRE(std::is_volatile_v<std::remove_pointer_t<decltype(v_from_byte_cast)>>);

	const volatile int* cv_int_ptr = &my_int;
	const volatile byte* cv_as_byte = reinterpret_cast<const volatile byte*>(cv_int_ptr);
	auto cv_from_byte_cast = byte_cast(cv_int_ptr);

	REQUIRE(cv_from_byte_cast == cv_as_byte);
	REQUIRE(std::is_const_v<std::remove_pointer_t<decltype(cv_from_byte_cast)>>);
	REQUIRE(std::is_volatile_v<std::remove_pointer_t<decltype(cv_from_byte_cast)>>);
}

TEST_CASE("core/casts: byte_cast returns correct values", "[core]")
{
	float* f = new float;
	REQUIRE(byte_cast(f) == reinterpret_cast<byte*>(f));
	delete f;

	struct trivial_type { };
	trivial_type* t = new trivial_type;
	REQUIRE(byte_cast(t) == reinterpret_cast<byte*>(t));
	delete t;

	std::size_t* s = new std::size_t;
	REQUIRE(byte_cast(s) == reinterpret_cast<byte*>(s));
	delete s;
}

TEST_CASE("core/casts: saturate_cast returns correct values", "[core]")
{
	int i = 20;
	REQUIRE(saturate_cast<float>(i) == 20.0f);

	float f = std::numeric_limits<float>::max();
	REQUIRE(saturate_cast<int>(f) == std::numeric_limits<int>::max());

	f = std::numeric_limits<float>::lowest();
	REQUIRE(saturate_cast<uint>(f) == 0u);

	i = std::numeric_limits<int>::max();
	REQUIRE(saturate_cast<uint>(i) == static_cast<uint>(i));

	uint u = std::numeric_limits<uint>::max();
	REQUIRE(saturate_cast<int>(u) == std::numeric_limits<int>::max());

	i = std::numeric_limits<int>::min();
	REQUIRE(saturate_cast<uint>(i) == 0u);

	llong l = std::numeric_limits<llong>::max();
	REQUIRE(saturate_cast<int>(l) == std::numeric_limits<int>::max());
}

TEST_CASE("core/casts: narrow_cast returns correct values", "[core]")
{
	int i = 20;
	REQUIRE(narrow_cast<float>(i) == static_cast<float>(i));

	i = std::numeric_limits<int>::max();
	REQUIRE(narrow_cast<uint>(i) == static_cast<uint>(i));
}

TEST_CASE("core/casts: overload_cast selects the correct overload", "[core]")
{
	auto ptr1 = overload_cast<void()>(&overload);
	REQUIRE(ptr1 == static_cast<void(*)()>(&overload));

	auto ptr2 = overload_cast<void(int)>(&overload);
	REQUIRE(ptr2 == static_cast<void(*)(int)>(&overload));

	auto ptr3 = overload_cast<int(std::nullptr_t)>(&overload);
	REQUIRE(ptr3 == static_cast<int(*)(std::nullptr_t)>(&overload));

	auto ptr4 = overload_cast<int(float)>(&overload);
	REQUIRE(ptr4 == static_cast<int(*)(float)>(&overload));

	auto ptr_t1 = overload_cast<void()>(&test::overload);
	REQUIRE(ptr_t1 == static_cast<void(test::*)()>(&test::overload));

	auto ptr_t2 = overload_cast<void(int)>(&test::overload);
	REQUIRE(ptr_t2 == static_cast<void(test::*)(int)>(&test::overload));

	auto ptr_t3 = overload_cast<int(std::nullptr_t)>(&test::overload);
	REQUIRE(ptr_t3 == static_cast<int(test::*)(std::nullptr_t)>(&test::overload));

	auto ptr_t4 = overload_cast<void(int) const>(&test::overload);
	REQUIRE(ptr_t4 == static_cast<void(test::*)(int) const>(&test::overload));

	auto ptr_t5 = overload_cast<int(float)>(&test::overload);
	REQUIRE(ptr_t5 == static_cast<int(test::*)(float) const>(&test::overload));
}
