#include <mtk/core/math.hpp>

#include <mtk/core/assert.hpp>

#include <cmath>

namespace mtk {
namespace {

template<class T>
T
_factorial(T t) noexcept
{
	MTK_IMPL_LIB_ASSERT(t >= T());
	return std::tgamma(t + T(1));
}

} // namespace

float
factorial(float t)
{
	return _factorial(t);
}

double
factorial(double t)
{
	return _factorial(t);
}

ldouble
factorial(ldouble t)
{
	return _factorial(t);
}

} // namespace mtk
