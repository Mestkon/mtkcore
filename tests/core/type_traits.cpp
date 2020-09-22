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

