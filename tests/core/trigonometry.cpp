#include <catch.hpp>

#include <mtk/core/trigonometry.hpp>

using namespace mtk;

namespace mtk {
template<class T, class D>
std::ostream&
operator<<(std::ostream& os, const impl_core::angle_base<T, D>& val)
{
	os << static_cast<const D&>(val).value();
	return os;
}

}

constexpr radians rad_zero(0.0);
constexpr radians rad_half(math::pi<real>);
constexpr radians rad_one_fourths = rad_half / 2.0;
constexpr radians rad_three_fourths = rad_half + rad_one_fourths;
constexpr radians rad_five_eighths = rad_half + rad_one_fourths / 2.0;

constexpr degrees deg_zero(0.0);
constexpr degrees deg_half(180.0);
constexpr degrees deg_one_fourths = deg_half / 2.0;
constexpr degrees deg_three_fourths = deg_half + deg_one_fourths;
constexpr degrees deg_five_eighths = deg_half + deg_one_fourths / 2.0;

TEST_CASE("core/trigonometry: radians", "[core]")
{
	constexpr real rad_zero(0.0);
	constexpr real rad_half(math::pi<real>);
	constexpr real rad_one_fourths = rad_half / 2.0;
	constexpr real rad_three_fourths = rad_half + rad_one_fourths;
	constexpr real rad_five_eighths = rad_half + rad_one_fourths / 2.0;

	REQUIRE(radians<real>().value() == 0.0);
	REQUIRE(radians(rad_zero).value() == rad_zero);
	REQUIRE(radians(rad_half).value() == rad_half);
	REQUIRE(radians(rad_one_fourths).value() == rad_one_fourths);
	REQUIRE(radians(rad_three_fourths).value() == rad_three_fourths);
	REQUIRE(radians(rad_five_eighths).value() == rad_five_eighths);
}


TEST_CASE("core/trigonometry: degrees", "[core]")
{
	constexpr real deg_zero(0.0);
	constexpr real deg_half(180.0);
	constexpr real deg_one_fourths = deg_half / 2.0;
	constexpr real deg_three_fourths = deg_half + deg_one_fourths;
	constexpr real deg_five_eighths = deg_half + deg_one_fourths / 2.0;

	REQUIRE(degrees<real>().value() == 0.0);
	REQUIRE(degrees(deg_zero).value() == deg_zero);
	REQUIRE(degrees(deg_half).value() == deg_half);
	REQUIRE(degrees(deg_one_fourths).value() == deg_one_fourths);
	REQUIRE(degrees(deg_three_fourths).value() == deg_three_fourths);
	REQUIRE(degrees(deg_five_eighths).value() == deg_five_eighths);
}

TEST_CASE("core/trigonometry: equivalence comparison returns sensible values", "[core]")
{
	REQUIRE(rad_zero == radians(rad_zero));
	REQUIRE(rad_half == radians(rad_half));
	REQUIRE(rad_one_fourths == radians(rad_one_fourths));
	REQUIRE(rad_three_fourths == radians(rad_three_fourths));
	REQUIRE(rad_five_eighths == radians(rad_five_eighths));

	REQUIRE(rad_zero != radians(rad_half));
	REQUIRE(rad_one_fourths != radians(rad_three_fourths));
	REQUIRE(rad_five_eighths != radians(rad_zero));

	REQUIRE(deg_zero == degrees(deg_zero));
	REQUIRE(deg_half == degrees(deg_half));
	REQUIRE(deg_one_fourths == degrees(deg_one_fourths));
	REQUIRE(deg_three_fourths == degrees(deg_three_fourths));
	REQUIRE(deg_five_eighths == degrees(deg_five_eighths));

	REQUIRE(deg_zero != degrees(deg_half));
	REQUIRE(deg_one_fourths != degrees(deg_three_fourths));
	REQUIRE(deg_five_eighths != degrees(deg_zero));
}

TEST_CASE("core/trigonometry: order comparison returns sensible values", "[core]")
{
	REQUIRE(rad_zero < rad_half);
	REQUIRE(rad_one_fourths < rad_three_fourths);
	REQUIRE(!(rad_five_eighths < rad_zero));

	REQUIRE(rad_five_eighths > rad_one_fourths);
	REQUIRE(rad_three_fourths > rad_half);
	REQUIRE(!(rad_zero > rad_five_eighths));

	REQUIRE(rad_half <= rad_three_fourths);
	REQUIRE(rad_one_fourths <= rad_five_eighths);
	REQUIRE(rad_three_fourths <= radians(rad_three_fourths));
	REQUIRE(!(rad_five_eighths <= rad_zero));

	REQUIRE(rad_three_fourths >= rad_half);
	REQUIRE(rad_one_fourths >= rad_zero);
	REQUIRE(rad_half >= radians(rad_half));
	REQUIRE(!(rad_zero >= rad_five_eighths));

	REQUIRE(deg_zero < deg_half);
	REQUIRE(deg_one_fourths < deg_three_fourths);
	REQUIRE(!(deg_five_eighths < deg_zero));

	REQUIRE(deg_five_eighths > deg_one_fourths);
	REQUIRE(deg_three_fourths > deg_half);
	REQUIRE(!(deg_zero > deg_five_eighths));

	REQUIRE(deg_half <= deg_three_fourths);
	REQUIRE(deg_one_fourths <= deg_five_eighths);
	REQUIRE(deg_three_fourths <= degrees(deg_three_fourths));
	REQUIRE(!(deg_five_eighths <= deg_zero));

	REQUIRE(deg_three_fourths >= deg_half);
	REQUIRE(deg_one_fourths >= deg_zero);
	REQUIRE(deg_half >= degrees(deg_half));
	REQUIRE(!(deg_zero >= deg_five_eighths));
}

TEST_CASE("core/trigonometry: unary operators returns the correct value", "[core]")
{
	REQUIRE(+rad_zero == rad_zero);
	REQUIRE(+rad_half == rad_half);
	REQUIRE(+rad_one_fourths == rad_one_fourths);
	REQUIRE(+rad_three_fourths == rad_three_fourths);
	REQUIRE(+rad_five_eighths == rad_five_eighths);

	REQUIRE(-rad_zero == radians(-rad_zero.value()));
	REQUIRE(-rad_half == radians(-rad_half.value()));
	REQUIRE(-rad_one_fourths == radians(-rad_one_fourths.value()));
	REQUIRE(-rad_three_fourths == radians(-rad_three_fourths.value()));
	REQUIRE(-rad_five_eighths == radians(-rad_five_eighths.value()));

	REQUIRE(+deg_zero == deg_zero);
	REQUIRE(+deg_half == deg_half);
	REQUIRE(+deg_one_fourths == deg_one_fourths);
	REQUIRE(+deg_three_fourths == deg_three_fourths);
	REQUIRE(+deg_five_eighths == deg_five_eighths);

	REQUIRE(-deg_zero == degrees(-deg_zero.value()));
	REQUIRE(-deg_half == degrees(-deg_half.value()));
	REQUIRE(-deg_one_fourths == degrees(-deg_one_fourths.value()));
	REQUIRE(-deg_three_fourths == degrees(-deg_three_fourths.value()));
	REQUIRE(-deg_five_eighths == degrees(-deg_five_eighths.value()));
}

TEST_CASE("core/trigonometry: binary operators returns the correct value", "[core]")
{
	REQUIRE(rad_zero + rad_half == Approx(rad_half));
	REQUIRE(rad_one_fourths + rad_one_fourths + rad_one_fourths == Approx(rad_three_fourths));
	REQUIRE(rad_three_fourths - rad_one_fourths == Approx(rad_half));
	REQUIRE(rad_one_fourths*3 == Approx(rad_three_fourths));
	REQUIRE(2*rad_five_eighths / 5 == Approx(rad_one_fourths));
	REQUIRE(rad_three_fourths / rad_one_fourths == Approx(3));

	REQUIRE(deg_zero + deg_half == Approx(deg_half));
	REQUIRE(deg_one_fourths + deg_one_fourths + deg_one_fourths == Approx(deg_three_fourths));
	REQUIRE(deg_three_fourths - deg_one_fourths == Approx(deg_half));
	REQUIRE(deg_one_fourths*3 == Approx(deg_three_fourths));
	REQUIRE(2*deg_five_eighths / 5 == Approx(deg_one_fourths));
	REQUIRE(deg_three_fourths / deg_one_fourths == Approx(3));
}

TEST_CASE("core/trigonometry: to_radians/to_degrees returns the converted value", "[core]")
{
	REQUIRE(rad_zero == Approx(to_radians(deg_zero)));
	REQUIRE(rad_zero == to_radians(rad_zero));
	REQUIRE(to_degrees(rad_zero) == Approx(deg_zero));
	REQUIRE(to_degrees(deg_zero) == deg_zero);

	REQUIRE(rad_half == Approx(to_radians(deg_half)));
	REQUIRE(rad_half == to_radians(rad_half));
	REQUIRE(to_degrees(rad_half) == Approx(deg_half));
	REQUIRE(to_degrees(deg_half) == deg_half);

	REQUIRE(rad_one_fourths == Approx(to_radians(deg_one_fourths)));
	REQUIRE(rad_one_fourths == to_radians(rad_one_fourths));
	REQUIRE(to_degrees(rad_one_fourths) == Approx(deg_one_fourths));
	REQUIRE(to_degrees(deg_one_fourths) == deg_one_fourths);

	REQUIRE(rad_three_fourths == Approx(to_radians(deg_three_fourths)));
	REQUIRE(rad_three_fourths == to_radians(rad_three_fourths));
	REQUIRE(to_degrees(rad_three_fourths) == Approx(deg_three_fourths));
	REQUIRE(to_degrees(deg_three_fourths) == deg_three_fourths);

	REQUIRE(rad_five_eighths == Approx(to_radians(deg_five_eighths)));
	REQUIRE(rad_five_eighths == to_radians(rad_five_eighths));
	REQUIRE(to_degrees(rad_five_eighths) == Approx(deg_five_eighths));
	REQUIRE(to_degrees(deg_five_eighths) == deg_five_eighths);
}

TEST_CASE("core/trigonometry: trig functions return the correct value", "[core]")
{
	REQUIRE(sin(rad_zero) == Approx(std::sin(rad_zero.value())));
	REQUIRE(sin(rad_half) == Approx(std::sin(rad_half.value())));
	REQUIRE(sin(rad_one_fourths) == Approx(std::sin(rad_one_fourths.value())));
	REQUIRE(sin(rad_three_fourths) == Approx(std::sin(rad_three_fourths.value())));
	REQUIRE(sin(rad_five_eighths) == Approx(std::sin(rad_five_eighths.value())));
	REQUIRE(sin(-rad_half) == Approx(std::sin(-rad_half.value())));
	REQUIRE(sin(-rad_one_fourths) == Approx(std::sin(-rad_one_fourths.value())));
	REQUIRE(sin(-rad_three_fourths) == Approx(std::sin(-rad_three_fourths.value())));
	REQUIRE(sin(-rad_five_eighths) == Approx(std::sin(-rad_five_eighths.value())));

	REQUIRE(sin(deg_zero) == Approx(std::sin(rad_zero.value())));
	REQUIRE(sin(deg_half) == Approx(std::sin(rad_half.value())));
	REQUIRE(sin(deg_one_fourths) == Approx(std::sin(rad_one_fourths.value())));
	REQUIRE(sin(deg_three_fourths) == Approx(std::sin(rad_three_fourths.value())));
	REQUIRE(sin(deg_five_eighths) == Approx(std::sin(rad_five_eighths.value())));
	REQUIRE(sin(-deg_half) == Approx(std::sin(-rad_half.value())));
	REQUIRE(sin(-deg_one_fourths) == Approx(std::sin(-rad_one_fourths.value())));
	REQUIRE(sin(-deg_three_fourths) == Approx(std::sin(-rad_three_fourths.value())));
	REQUIRE(sin(-deg_five_eighths) == Approx(std::sin(-rad_five_eighths.value())));


	REQUIRE(cos(rad_zero) == Approx(std::cos(rad_zero.value())));
	REQUIRE(cos(rad_half) == Approx(std::cos(rad_half.value())));
	REQUIRE(cos(rad_one_fourths) == Approx(std::cos(rad_one_fourths.value())));
	REQUIRE(cos(rad_three_fourths) == Approx(std::cos(rad_three_fourths.value())));
	REQUIRE(cos(rad_five_eighths) == Approx(std::cos(rad_five_eighths.value())));
	REQUIRE(cos(-rad_half) == Approx(std::cos(-rad_half.value())));
	REQUIRE(cos(-rad_one_fourths) == Approx(std::cos(-rad_one_fourths.value())));
	REQUIRE(cos(-rad_three_fourths) == Approx(std::cos(-rad_three_fourths.value())));
	REQUIRE(cos(-rad_five_eighths) == Approx(std::cos(-rad_five_eighths.value())));

	REQUIRE(cos(deg_zero) == Approx(std::cos(rad_zero.value())));
	REQUIRE(cos(deg_half) == Approx(std::cos(rad_half.value())));
	REQUIRE(cos(deg_one_fourths) == Approx(std::cos(rad_one_fourths.value())));
	REQUIRE(cos(deg_three_fourths) == Approx(std::cos(rad_three_fourths.value())));
	REQUIRE(cos(deg_five_eighths) == Approx(std::cos(rad_five_eighths.value())));
	REQUIRE(cos(-deg_half) == Approx(std::cos(-rad_half.value())));
	REQUIRE(cos(-deg_one_fourths) == Approx(std::cos(-rad_one_fourths.value())));
	REQUIRE(cos(-deg_three_fourths) == Approx(std::cos(-rad_three_fourths.value())));
	REQUIRE(cos(-deg_five_eighths) == Approx(std::cos(-rad_five_eighths.value())));

	REQUIRE(tan(rad_zero) == Approx(std::tan(rad_zero.value())));
	REQUIRE(tan(rad_half) == Approx(std::tan(rad_half.value())));
	REQUIRE(tan(rad_one_fourths) == Approx(std::tan(rad_one_fourths.value())));
	REQUIRE(tan(rad_three_fourths) == Approx(std::tan(rad_three_fourths.value())));
	REQUIRE(tan(rad_five_eighths) == Approx(std::tan(rad_five_eighths.value())));
	REQUIRE(tan(-rad_half) == Approx(std::tan(-rad_half.value())));
	REQUIRE(tan(-rad_one_fourths) == Approx(std::tan(-rad_one_fourths.value())));
	REQUIRE(tan(-rad_three_fourths) == Approx(std::tan(-rad_three_fourths.value())));
	REQUIRE(tan(-rad_five_eighths) == Approx(std::tan(-rad_five_eighths.value())));

	REQUIRE(tan(deg_zero) == Approx(std::tan(rad_zero.value())));
	REQUIRE(tan(deg_half) == Approx(std::tan(rad_half.value())));
	REQUIRE(tan(deg_one_fourths) == Approx(std::tan(rad_one_fourths.value())));
	REQUIRE(tan(deg_three_fourths) == Approx(std::tan(rad_three_fourths.value())));
	REQUIRE(tan(deg_five_eighths) == Approx(std::tan(rad_five_eighths.value())));
	REQUIRE(tan(-deg_half) == Approx(std::tan(-rad_half.value())));
	REQUIRE(tan(-deg_one_fourths) == Approx(std::tan(-rad_one_fourths.value())));
	REQUIRE(tan(-deg_three_fourths) == Approx(std::tan(-rad_three_fourths.value())));
	REQUIRE(tan(-deg_five_eighths) == Approx(std::tan(-rad_five_eighths.value())));

	mtk::radians rad_small(0.0000000000001);
	mtk::degrees deg_small(0.0000000000001);
	REQUIRE(csc(rad_zero - rad_small) < -1000.0);
	REQUIRE(csc(rad_zero + rad_small) > 1000.0);
	REQUIRE(csc(rad_half - rad_small) > 1000.0);
	REQUIRE(csc(rad_half + rad_small) < -1000.0);
	REQUIRE(csc(rad_one_fourths) == Approx(1));
	REQUIRE(csc(rad_three_fourths) == Approx(-1));
	REQUIRE(csc(rad_five_eighths) == Approx(-std::sqrt(2)));
	REQUIRE(csc(-rad_half - rad_small) > 1000.0);
	REQUIRE(csc(-rad_half + rad_small) < -1000.0);
	REQUIRE(csc(-rad_one_fourths) == Approx(-1));
	REQUIRE(csc(-rad_three_fourths) == Approx(1));
	REQUIRE(csc(-rad_five_eighths) == Approx(std::sqrt(2)));

	REQUIRE(csc(deg_zero - deg_small) < -1000.0);
	REQUIRE(csc(deg_zero + deg_small) > 1000.0);
	REQUIRE(csc(deg_half - deg_small) > 1000.0);
	REQUIRE(csc(deg_half + deg_small) < -1000.0);
	REQUIRE(csc(deg_one_fourths) == Approx(1));
	REQUIRE(csc(deg_three_fourths) == Approx(-1));
	REQUIRE(csc(deg_five_eighths) == Approx(-std::sqrt(2)));
	REQUIRE(csc(-deg_half - deg_small) > 1000.0);
	REQUIRE(csc(-deg_half + deg_small) < -1000.0);
	REQUIRE(csc(-deg_one_fourths) == Approx(-1));
	REQUIRE(csc(-deg_three_fourths) == Approx(1));
	REQUIRE(csc(-deg_five_eighths) == Approx(std::sqrt(2)));

	REQUIRE(sec(rad_zero) == Approx(1));
	REQUIRE(sec(rad_half) == Approx(-1));
	REQUIRE(sec(rad_one_fourths - rad_small) > 1000.0);
	REQUIRE(sec(rad_one_fourths + rad_small) < -1000.0);
	REQUIRE(sec(rad_three_fourths - rad_small) < -1000.0);
	REQUIRE(sec(rad_three_fourths + rad_small) > 1000.0);
	REQUIRE(sec(rad_five_eighths) == Approx(-std::sqrt(2)));
	REQUIRE(sec(-rad_half) == Approx(-1));
	REQUIRE(sec(-rad_one_fourths + rad_small) > 1000.0);
	REQUIRE(sec(-rad_one_fourths - rad_small) < -1000.0);
	REQUIRE(sec(-rad_three_fourths + rad_small) < -1000.0);
	REQUIRE(sec(-rad_three_fourths - rad_small) > 1000.0);
	REQUIRE(sec(-rad_five_eighths) == Approx(-std::sqrt(2)));

	REQUIRE(sec(deg_zero) == Approx(1));
	REQUIRE(sec(deg_half) == Approx(-1));
	REQUIRE(sec(deg_one_fourths - deg_small) > 1000.0);
	REQUIRE(sec(deg_one_fourths + deg_small) < -1000.0);
	REQUIRE(sec(deg_three_fourths - deg_small) < -1000.0);
	REQUIRE(sec(deg_three_fourths + deg_small) > 1000.0);
	REQUIRE(sec(deg_five_eighths) == Approx(-std::sqrt(2)));
	REQUIRE(sec(-deg_half) == Approx(-1));
	REQUIRE(sec(-deg_one_fourths + deg_small) > 1000.0);
	REQUIRE(sec(-deg_one_fourths - deg_small) < -1000.0);
	REQUIRE(sec(-deg_three_fourths + deg_small) < -1000.0);
	REQUIRE(sec(-deg_three_fourths - deg_small) > 1000.0);
	REQUIRE(sec(-deg_five_eighths) == Approx(-std::sqrt(2)));

	REQUIRE(cot(rad_zero - rad_small) < -1000.0);
	REQUIRE(cot(rad_zero + rad_small) > 1000.0);
	REQUIRE(cot(rad_half - rad_small) < -1000.0);
	REQUIRE(cot(rad_half + rad_small) > 1000.0);
	REQUIRE(cot(rad_one_fourths) == Approx(0));
	REQUIRE(cot(rad_three_fourths) == Approx(0));
	REQUIRE(cot(rad_five_eighths) == Approx(1));
	REQUIRE(cot(-rad_half - rad_small) < -1000.0);
	REQUIRE(cot(-rad_half + rad_small) > 1000.0);
	REQUIRE(cot(-rad_one_fourths) == Approx(0));
	REQUIRE(cot(-rad_three_fourths) == Approx(0));
	REQUIRE(cot(-rad_five_eighths) == Approx(-1));


	REQUIRE(cot(deg_zero - deg_small) < -1000.0);
	REQUIRE(cot(deg_zero + deg_small) > 1000.0);
	REQUIRE(cot(deg_half - deg_small) < -1000.0);
	REQUIRE(cot(deg_half + deg_small) > 1000.0);
	REQUIRE(cot(deg_one_fourths) == Approx(0));
	REQUIRE(cot(deg_three_fourths) == Approx(0));
	REQUIRE(cot(deg_five_eighths) == Approx(1));
	REQUIRE(cot(-deg_half - deg_small) < -1000.0);
	REQUIRE(cot(-deg_half + deg_small) > 1000.0);
	REQUIRE(cot(-deg_one_fourths) == Approx(0));
	REQUIRE(cot(-deg_three_fourths) == Approx(0));
	REQUIRE(cot(-deg_five_eighths) == Approx(-1));
}

TEST_CASE("core/trigonometry: inverse trig functions return the correct value", "[core]")
{
	REQUIRE(mtk::asin(mtk::sin(rad_zero)) == Approx(rad_zero));
	REQUIRE(mtk::asin(mtk::sin(rad_half)) == Approx(rad_zero));
	REQUIRE(mtk::asin(mtk::sin(rad_one_fourths)) == Approx(rad_one_fourths));
	REQUIRE(mtk::asin(mtk::sin(rad_three_fourths)) == Approx(-rad_one_fourths));
	REQUIRE(mtk::asin(mtk::sin(rad_five_eighths)) == Approx(-rad_five_eighths / 5));
	REQUIRE(mtk::asin(mtk::sin(-rad_half)) == Approx(rad_zero));
	REQUIRE(mtk::asin(mtk::sin(-rad_one_fourths)) == Approx(-rad_one_fourths));
	REQUIRE(mtk::asin(mtk::sin(-rad_three_fourths)) == Approx(rad_one_fourths));
	REQUIRE(mtk::asin(mtk::sin(-rad_five_eighths)) == Approx(rad_five_eighths / 5));

	REQUIRE(mtk::acos(mtk::cos(rad_zero)) == Approx(rad_zero));
	REQUIRE(mtk::acos(mtk::cos(rad_half)) == Approx(rad_half));
	REQUIRE(mtk::acos(mtk::cos(rad_one_fourths)) == Approx(rad_one_fourths));
	REQUIRE(mtk::acos(mtk::cos(rad_three_fourths)) == Approx(rad_one_fourths));
	REQUIRE(mtk::acos(mtk::cos(rad_five_eighths)) == Approx(3*rad_five_eighths / 5));
	REQUIRE(mtk::acos(mtk::cos(-rad_half)) == Approx(rad_half));
	REQUIRE(mtk::acos(mtk::cos(-rad_one_fourths)) == Approx(rad_one_fourths));
	REQUIRE(mtk::acos(mtk::cos(-rad_three_fourths)) == Approx(rad_one_fourths));
	REQUIRE(mtk::acos(mtk::cos(-rad_five_eighths)) == Approx(3*rad_five_eighths / 5));

	mtk::radians rad_small(0.0000000000001);

	REQUIRE(mtk::atan(mtk::tan(rad_zero)) == Approx(rad_zero));
	REQUIRE(mtk::atan(mtk::tan(rad_half)) == Approx(rad_zero));
	REQUIRE(mtk::atan(mtk::tan(rad_one_fourths - rad_small)) == Approx(rad_one_fourths));
	REQUIRE(mtk::atan(mtk::tan(rad_three_fourths + rad_small)) == Approx(-rad_one_fourths));
	REQUIRE(mtk::atan(mtk::tan(rad_five_eighths)) == Approx(rad_five_eighths / 5));
	REQUIRE(mtk::atan(mtk::tan(-rad_half)) == Approx(rad_zero));
	REQUIRE(mtk::atan(mtk::tan(-rad_one_fourths + rad_small)) == Approx(-rad_one_fourths));
	REQUIRE(mtk::atan(mtk::tan(-rad_three_fourths - rad_small)) == Approx(rad_one_fourths));
	REQUIRE(mtk::atan(mtk::tan(-rad_five_eighths)) == Approx(-rad_five_eighths / 5));

	REQUIRE(mtk::atan2(mtk::sin(rad_zero), mtk::cos(rad_zero)) == Approx(rad_zero));
	REQUIRE(mtk::atan2(mtk::sin(rad_half), mtk::cos(rad_half)) == Approx(rad_half));
	REQUIRE(mtk::atan2(mtk::sin(rad_one_fourths), mtk::cos(rad_one_fourths)) == Approx(rad_one_fourths));
	REQUIRE(mtk::atan2(mtk::sin(rad_three_fourths), mtk::cos(rad_three_fourths)) == Approx(-rad_one_fourths));
	REQUIRE(mtk::atan2(mtk::sin(rad_five_eighths), mtk::cos(rad_five_eighths)) == Approx(-3*rad_five_eighths / 5));
	REQUIRE(mtk::atan2(mtk::sin(-rad_half), mtk::cos(-rad_half)) == Approx(-rad_half));
	REQUIRE(mtk::atan2(mtk::sin(-rad_one_fourths), mtk::cos(-rad_one_fourths)) == Approx(-rad_one_fourths));
	REQUIRE(mtk::atan2(mtk::sin(-rad_three_fourths), mtk::cos(-rad_three_fourths)) == Approx(rad_one_fourths));
	REQUIRE(mtk::atan2(mtk::sin(-rad_five_eighths), mtk::cos(-rad_five_eighths)) == Approx(3*rad_five_eighths / 5));

	REQUIRE(mtk::acsc(mtk::csc(rad_zero)) == Approx(rad_zero));
	REQUIRE(mtk::acsc(mtk::csc(rad_half)) == Approx(rad_zero));
	REQUIRE(mtk::acsc(mtk::csc(rad_one_fourths)) == Approx(rad_one_fourths));
	REQUIRE(mtk::acsc(mtk::csc(rad_three_fourths)) == Approx(-rad_one_fourths));
	REQUIRE(mtk::acsc(mtk::csc(rad_five_eighths)) == Approx(-rad_five_eighths / 5));
	REQUIRE(mtk::acsc(mtk::csc(-rad_half)) == Approx(rad_zero));
	REQUIRE(mtk::acsc(mtk::csc(-rad_one_fourths)) == Approx(-rad_one_fourths));
	REQUIRE(mtk::acsc(mtk::csc(-rad_three_fourths)) == Approx(rad_one_fourths));
	REQUIRE(mtk::acsc(mtk::csc(-rad_five_eighths)) == Approx(rad_five_eighths / 5));

	REQUIRE(mtk::asec(mtk::sec(rad_zero)) == Approx(rad_zero));
	REQUIRE(mtk::asec(mtk::sec(rad_half)) == Approx(rad_half));
	REQUIRE(mtk::asec(mtk::sec(rad_one_fourths)) == Approx(rad_one_fourths));
	REQUIRE(mtk::asec(mtk::sec(rad_three_fourths)) == Approx(rad_one_fourths));
	REQUIRE(mtk::asec(mtk::sec(rad_five_eighths)) == Approx(3*rad_five_eighths / 5));
	REQUIRE(mtk::asec(mtk::sec(-rad_half)) == Approx(rad_half));
	REQUIRE(mtk::asec(mtk::sec(-rad_one_fourths)) == Approx(rad_one_fourths));
	REQUIRE(mtk::asec(mtk::sec(-rad_three_fourths)) == Approx(rad_one_fourths));
	REQUIRE(mtk::asec(mtk::sec(-rad_five_eighths)) == Approx(3*rad_five_eighths / 5));

	REQUIRE(mtk::acot(mtk::cot(rad_zero)) == Approx(rad_zero));
	REQUIRE(mtk::acot(mtk::cot(rad_half)) == Approx(rad_zero));
	REQUIRE(mtk::acot(mtk::cot(rad_one_fourths - rad_small)) == Approx(rad_one_fourths));
	REQUIRE(mtk::acot(mtk::cot(rad_three_fourths + rad_small)) == Approx(-rad_one_fourths));
	REQUIRE(mtk::acot(mtk::cot(rad_five_eighths)) == Approx(rad_five_eighths / 5));
	REQUIRE(mtk::acot(mtk::cot(-rad_half)) == Approx(rad_zero));
	REQUIRE(mtk::acot(mtk::cot(-rad_one_fourths - rad_small)) == Approx(rad_one_fourths));
	REQUIRE(mtk::acot(mtk::cot(-rad_three_fourths + rad_small)) == Approx(-rad_one_fourths));
	REQUIRE(mtk::acot(mtk::cot(-rad_five_eighths)) == Approx(-rad_five_eighths / 5));
}
