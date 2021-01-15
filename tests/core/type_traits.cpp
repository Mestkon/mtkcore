#include <catch.hpp>

#include <mtk/core/type_traits.hpp>

#include <complex>

using namespace mtk;

TEST_CASE("core/type_traits: make_real does the thing", "[core]")
{
	using real_float = make_real_t<float>;
	using real_double = make_real_t<double>;
	using real_ulong = make_real_t<ulong>;
	using real_short = make_real_t<short>;
	using real_cpx_fl = make_real_t<std::complex<float>>;

	REQUIRE((std::is_same_v<real_float, float>));
	REQUIRE((std::is_same_v<real_double, double>));
	REQUIRE((std::is_same_v<real_ulong, real>));
	REQUIRE((std::is_same_v<real_short, real>));
	REQUIRE((std::is_same_v<real_cpx_fl, float>));
}

TEST_CASE("core/type_traits: promote does the thing", "[core]")
{
	using pm_short = promote_t<short>;
	using pm_uint = promote_t<uint>;
	using pm_flt = promote_t<float>;

	REQUIRE(sizeof(pm_short) > sizeof(short));
	REQUIRE(std::is_signed_v<pm_short>);
	REQUIRE(std::numeric_limits<pm_short>::lowest() < std::numeric_limits<short>::lowest());
	REQUIRE(std::numeric_limits<pm_short>::max() > std::numeric_limits<short>::max());
	REQUIRE(sizeof(pm_uint) > sizeof(uint));
	REQUIRE(std::is_signed_v<pm_uint>);
	REQUIRE(std::numeric_limits<pm_uint>::lowest() < std::numeric_limits<uint>::lowest());
	REQUIRE(std::numeric_limits<pm_uint>::max() > std::numeric_limits<uint>::max());
	REQUIRE(sizeof(pm_flt) > sizeof(float));
	REQUIRE(std::numeric_limits<pm_flt>::lowest() < std::numeric_limits<float>::lowest());
	REQUIRE(std::numeric_limits<pm_flt>::max() > std::numeric_limits<float>::max());
}

template<class T>
T af_test_func(T t)
{
	if constexpr (std::is_integral_v<T>) {
		return t;
	} else {
		static_assert(always_false_v<T>);
	}
}

TEST_CASE("core/type_traits: always_false is actually false", "[core]")
{
	struct S { };

	REQUIRE(always_false_v<int> == false);
	REQUIRE(always_false_v<std::nullptr_t> == false);
	REQUIRE(always_false_v<double> == false);
	REQUIRE(always_false_v<S> == false);

	REQUIRE(af_test_func(42) == 42);
	REQUIRE(af_test_func(69LL) == 69LL);
	REQUIRE(af_test_func('a') == 'a');
}
