#include <mtk/core/trigonometry.hpp>

#include <cmath>

namespace mtk {
namespace impl_core {
namespace core_trigonometry {
namespace {

template<class T>
T sin_impl(T val) { return std::sin(val); }
template<class T>
T cos_impl(T val) { return std::cos(val); }
template<class T>
T tan_impl(T val) { return std::tan(val); }
template<class T>
T asin_impl(T val) { return std::asin(val); }
template<class T>
T acos_impl(T val) { return std::acos(val); }
template<class T>
T atan_impl(T val) { return std::atan(val); }
template<class T>
T atan2_impl(T y, T x) { return std::atan2(y, x); }

} // namespace
} // namespace core_trigonometry



float sin(float val)
{
	return core_trigonometry::sin_impl(val);
}

double sin(double val)
{
	return core_trigonometry::sin_impl(val);
}

ldouble sin(ldouble val)
{
	return core_trigonometry::sin_impl(val);
}

float cos(float val)
{
	return core_trigonometry::cos_impl(val);
}

double cos(double val)
{
	return core_trigonometry::cos_impl(val);
}

ldouble cos(ldouble val)
{
	return core_trigonometry::cos_impl(val);
}

float tan(float val)
{
	return core_trigonometry::tan_impl(val);
}

double tan(double val)
{
	return core_trigonometry::tan_impl(val);
}

ldouble tan(ldouble val)
{
	return core_trigonometry::tan_impl(val);
}

float asin(float val)
{
	return core_trigonometry::asin_impl(val);
}

double asin(double val)
{
	return core_trigonometry::asin_impl(val);
}

ldouble asin(ldouble val)
{
	return core_trigonometry::asin_impl(val);
}

float acos(float val)
{
	return core_trigonometry::acos_impl(val);
}

double acos(double val)
{
	return core_trigonometry::acos_impl(val);
}

ldouble acos(ldouble val)
{
	return core_trigonometry::acos_impl(val);
}

float atan(float val)
{
	return core_trigonometry::atan_impl(val);
}

double atan(double val)
{
	return core_trigonometry::atan_impl(val);
}

ldouble atan(ldouble val)
{
	return core_trigonometry::atan_impl(val);
}

float atan2(float y, float x)
{
	return core_trigonometry::atan2_impl(y, x);
}

double atan2(double y, double x)
{
	return core_trigonometry::atan2_impl(y, x);
}

ldouble atan2(ldouble y, ldouble x)
{
	return core_trigonometry::atan2_impl(y, x);
}

} // namespace impl_core
} // namespace mtk
