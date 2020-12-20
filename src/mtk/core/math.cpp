#include <mtk/core/math.hpp>

#include <mtk/core/assert.hpp>

#include <cmath>

namespace mtk {
namespace core_math {
namespace {

template<class T>
T
_factorial(T t) noexcept
{
	MTK_IMPL_LIB_ASSERT(t >= T());
	return std::tgamma(t + T(1));
}

} // namespace
} // namespace core_math

float
factorial(float t)
{
	return core_math::_factorial(t);
}

double
factorial(double t)
{
	return core_math::_factorial(t);
}

ldouble
factorial(ldouble t)
{
	return core_math::_factorial(t);
}

} // namespace mtk
