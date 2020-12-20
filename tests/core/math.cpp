#include <catch.hpp>

#include <mtk/core/math.hpp>

using namespace mtk;

TEST_CASE("core/math: squared returns the square of the input", "[core]")
{
	int i_val = 4;
	REQUIRE(squared(i_val) == i_val*i_val);

	i_val = 0;
	REQUIRE(squared(i_val) == i_val*i_val);

	float f_val = 3.3f;
	REQUIRE(squared(f_val) == f_val*f_val);

	f_val = -17.29f;
	REQUIRE(squared(f_val) == f_val*f_val);

	if (std::numeric_limits<float>::has_infinity) {
		f_val = std::numeric_limits<float>::infinity();
		REQUIRE(squared(f_val) == f_val*f_val);
	}
}

TEST_CASE("core/math: cubed returns the cube of the input", "[core]")
{
	int i_val = 4;
	REQUIRE(cubed(i_val) == i_val*i_val*i_val);

	i_val = 0;
	REQUIRE(cubed(i_val) == i_val*i_val*i_val);

	float f_val = 3.3f;
	REQUIRE(cubed(f_val) == f_val*f_val*f_val);

	f_val = -17.29f;
	REQUIRE(cubed(f_val) == f_val*f_val*f_val);

	if (std::numeric_limits<float>::has_infinity) {
		f_val = std::numeric_limits<float>::infinity();
		REQUIRE(cubed(f_val) == f_val*f_val*f_val);
	}
}

TEST_CASE("core/math: to_radians/to_degrees returns the converted value", "[core]")
{
	constexpr real rad_zero(0.0);
	constexpr real rad_half(math::pi<real>);
	constexpr real rad_one_fourths = rad_half / 2.0;
	constexpr real rad_three_fourths = rad_half + rad_one_fourths;
	constexpr real rad_five_eighths = rad_half + rad_one_fourths / 2.0;

	constexpr real deg_zero(0.0);
	constexpr real deg_half(180.0);
	constexpr real deg_one_fourths = deg_half / 2.0;
	constexpr real deg_three_fourths = deg_half + deg_one_fourths;
	constexpr real deg_five_eighths = deg_half + deg_one_fourths / 2.0;

	REQUIRE(rad_zero == Approx(to_radians(deg_zero)));
	REQUIRE(to_degrees(rad_zero) == Approx(deg_zero));

	REQUIRE(rad_half == Approx(to_radians(deg_half)));
	REQUIRE(to_degrees(rad_half) == Approx(deg_half));

	REQUIRE(rad_one_fourths == Approx(to_radians(deg_one_fourths)));
	REQUIRE(to_degrees(rad_one_fourths) == Approx(deg_one_fourths));

	REQUIRE(rad_three_fourths == Approx(to_radians(deg_three_fourths)));
	REQUIRE(to_degrees(rad_three_fourths) == Approx(deg_three_fourths));

	REQUIRE(rad_five_eighths == Approx(to_radians(deg_five_eighths)));
	REQUIRE(to_degrees(rad_five_eighths) == Approx(deg_five_eighths));
}

TEST_CASE("core/math: sgn returns the sign of the input", "[core]")
{
	REQUIRE(sgn(27) == 1);
	REQUIRE(sgn(4) == 1);
	REQUIRE(sgn(1) == 1);
	REQUIRE(sgn(0) == 0);
	REQUIRE(sgn(-1) == -1);
	REQUIRE(sgn(-16) == -1);
	REQUIRE(sgn(-192) == -1);

	REQUIRE(sgn(0u) == 0u);
	REQUIRE(sgn(5u) == 1u);
	REQUIRE(sgn(10000u) == 1u);

	REQUIRE(sgn(-17.0f) == -1.0f);
	REQUIRE(sgn(-5.0f) == -1.0f);
	REQUIRE(sgn(0.0f) == 0.0f);
	REQUIRE(sgn(17.0f) == 1.0f);
	REQUIRE(sgn(99999.0f) == 1.0f);
	if (std::numeric_limits<float>::has_infinity) {
		 REQUIRE(sgn(std::numeric_limits<float>::infinity()) == 1.0f);
		 REQUIRE(sgn(-std::numeric_limits<float>::infinity()) == -1.0f);
	}
}

TEST_CASE("core/math: heaviside returns the result of the heaviside step function of the input", "[core]")
{
	REQUIRE(heaviside(27) == 1);
	REQUIRE(heaviside(4) == 1);
	REQUIRE(heaviside(1) == 1);
	REQUIRE(heaviside(0) == 0);
	REQUIRE(heaviside(-1) == 0);
	REQUIRE(heaviside(-16) == 0);
	REQUIRE(heaviside(-192) == 0);

	REQUIRE(heaviside(0u) == 0u);
	REQUIRE(heaviside(5u) == 1u);
	REQUIRE(heaviside(10000u) == 1u);

	REQUIRE(heaviside(-17.0f) == 0.0f);
	REQUIRE(heaviside(-5.0f) == 0.0f);
	REQUIRE(heaviside(0.0f) == 0.5f);
	REQUIRE(heaviside(17.0f) == 1.0f);
	REQUIRE(heaviside(99999.0f) == 1.0f);
	if (std::numeric_limits<float>::has_infinity) {
		 REQUIRE(heaviside(std::numeric_limits<float>::infinity()) == 1.0f);
		 REQUIRE(heaviside(-std::numeric_limits<float>::infinity()) == 0.0f);
	}
}

TEST_CASE("core/math: factorial returns the factorial of the input", "[core]")
{
	REQUIRE(factorial(0) == Approx(1.0));
	REQUIRE(factorial(1) == Approx(1.0));
	REQUIRE(factorial(2) == Approx(2.0));
	REQUIRE(factorial(5) == Approx(120.0));
	REQUIRE(factorial(10) == Approx(3628800.0));

	REQUIRE(factorial(0u) == Approx(1.0));
	REQUIRE(factorial(1u) == Approx(1.0));
	REQUIRE(factorial(2u) == Approx(2.0));
	REQUIRE(factorial(5u) == Approx(120.0));
	REQUIRE(factorial(10u) == Approx(3628800.0));

	REQUIRE(factorial(0.0f) == Approx(1.0f));
	REQUIRE(factorial(1.0f) == Approx(1.0f));
	REQUIRE(factorial(2.0f) == Approx(2.0f));
	REQUIRE(factorial(5.0f) == Approx(120.0f));
	REQUIRE(factorial(10.0f) == Approx(3628800.0f));
}

TEST_CASE("core/math: is_pow2 returns the correct value", "[core]")
{
	REQUIRE(is_pow2(1));
	REQUIRE(is_pow2(2));
	REQUIRE(is_pow2(4));
	REQUIRE(!is_pow2(7));
	REQUIRE(!is_pow2(19));
	REQUIRE(is_pow2(32));
	REQUIRE(is_pow2(1024));
	REQUIRE(!is_pow2(1337));
	REQUIRE(!is_pow2(42));
	REQUIRE(!is_pow2(69));
	REQUIRE(!is_pow2(420));
}

TEST_CASE("core/math: next_pow2 returns the correct value", "[core]")
{
	REQUIRE(next_pow2(1) == 1);
	REQUIRE(next_pow2(2) == 2);
	REQUIRE(next_pow2(7) == 8);
	REQUIRE(next_pow2(42) == 64);
	REQUIRE(next_pow2(69) == 128);
	REQUIRE(next_pow2(256) == 256);
	REQUIRE(next_pow2(420) == 512);
	REQUIRE(next_pow2(4200) == 8192);
	REQUIRE(next_pow2(4095) == 4096);
}
