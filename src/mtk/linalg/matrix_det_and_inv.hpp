#ifndef MTK_LINALG_MATRIX_DET_AND_INV_HPP
#define MTK_LINALG_MATRIX_DET_AND_INV_HPP

#include <../src/mtk/linalg/matrix_impl_fwd.hpp>

#include <mtk/core/type_traits.hpp>
#include <mtk/core/assert.hpp>

#include <cmath>
#include <optional>

namespace mtk {
namespace impl_linalg {

template<class Mat>
constexpr
auto
matrix_determinant2(const Mat& m)
{
	return (m.value(0, 0)*m.value(1, 1) - m.value(0, 1)*m.value(1, 0));
}

template<class Mat>
constexpr
auto
matrix_determinant3(const Mat& m) noexcept
{
	return (
		m.value(0, 0)*(
			m.value(1, 1)*m.value(2, 2) - m.value(1, 2)*m.value(2, 1))
		+ m.value(0, 1)*(
			m.value(1, 2)*m.value(2, 0) - m.value(1, 0)*m.value(2, 2))
		+ m.value(0, 2)*(
			m.value(1, 0)*m.value(2, 1) - m.value(1, 1)*m.value(2, 0)));
}

template<class Mat>
constexpr
auto
matrix_determinant4(const Mat& m) noexcept
{
	return (
		m.value(0, 0)*(
			+ m.value(1, 1)*(
				m.value(2, 2)*m.value(3, 3) - m.value(2, 3)*m.value(3, 2))
			+ m.value(1, 2)*(
				m.value(2, 3)*m.value(3, 1) - m.value(2, 1)*m.value(3, 3))
			+ m.value(1, 3)*(
				m.value(2, 1)*m.value(3, 2) - m.value(2, 2)*m.value(3, 1)))
		+ m.value(0, 1)*(
			+ m.value(1, 0)*(
				m.value(2, 3)*m.value(3, 2) - m.value(2, 2)*m.value(3, 3))
			+ m.value(1, 2)*(
				m.value(2, 0)*m.value(3, 3) - m.value(2, 3)*m.value(3, 0))
			+ m.value(1, 3)*(
				m.value(2, 2)*m.value(3, 0) - m.value(2, 0)*m.value(3, 2)))
		+ m.value(0, 2)*(
			+ m.value(1, 0)*(
				m.value(2, 1)*m.value(3, 3) - m.value(2, 3)*m.value(3, 1))
			+ m.value(1, 1)*(
				m.value(2, 3)*m.value(3, 0) - m.value(2, 0)*m.value(3, 3))
			+ m.value(1, 3)*(
				m.value(2, 0)*m.value(3, 1) - m.value(2, 1)*m.value(3, 0)))
		+ m.value(0, 3)*(
			+ m.value(1, 0)*(
				m.value(2, 2)*m.value(3, 1) - m.value(2, 1)*m.value(3, 2))
			+ m.value(1, 1)*(
				m.value(2, 0)*m.value(3, 2) - m.value(2, 2)*m.value(3, 0))
			+ m.value(1, 2)*(
				m.value(2, 1)*m.value(3, 0) - m.value(2, 0)*m.value(3, 1))));
}

template<class Mat>
constexpr
auto
matrix_determinant(const Mat& m)
{
	constexpr auto dim = std::decay_t<Mat>::dimension;
	if constexpr (dim == 2)
		return impl_linalg::matrix_determinant2(m);
	else if constexpr (dim == 3)
		return impl_linalg::matrix_determinant3(m);
	else if constexpr (dim == 4)
		return impl_linalg::matrix_determinant4(m);
	else
		MTK_ASSERT(false);
}



template<class Mat>
auto
matrix_inverse2(const Mat& m, bool& ok, typename Mat::value_type ep) noexcept
{
	using value_type = std::conditional_t<std::is_integral_v<typename Mat::value_type>,
		make_real_t<typename Mat::value_type>,
		typename Mat::value_type>;

	using ret_mat = typename matrix_traits<Mat>::template rebind<value_type, 2, 2, Mat::options>;
	const auto det = impl_linalg::matrix_determinant2(m);

	ok = (std::abs(det) > ep);
	if (!ok) {
		return ret_mat();
	}

	const auto det_inv = value_type(1) / det;

	const auto m11 =  static_cast<value_type>(m.value(1, 1))*det_inv;
	const auto m12 = -static_cast<value_type>(m.value(0, 1))*det_inv;
	const auto m21 = -static_cast<value_type>(m.value(1, 0))*det_inv;
	const auto m22 =  static_cast<value_type>(m.value(0, 0))*det_inv;

	return ret_mat{m11, m12, m21, m22};
}

template<class Mat>
auto
matrix_inverse3(const Mat& m, bool& ok, typename Mat::value_type ep) noexcept
{
	using value_type = std::conditional_t<std::is_integral_v<typename Mat::value_type>,
		make_real_t<typename Mat::value_type>,
		typename Mat::value_type>;

	using ret_mat = typename matrix_traits<Mat>::template rebind<value_type, 3, 3, Mat::options>;

	const auto c0 = static_cast<value_type>(m.value(1, 0)*m.value(2, 1) - m.value(1, 1)*m.value(2, 0));
	const auto c1 = static_cast<value_type>(m.value(1, 1)*m.value(2, 2) - m.value(1, 2)*m.value(2, 1));
	const auto c2 = static_cast<value_type>(m.value(1, 2)*m.value(2, 0) - m.value(1, 0)*m.value(2, 2));

	const auto det = m.value(0, 0)*c1 + m.value(0, 1)*c2 + m.value(0, 2)*c0;

	ok = (std::abs(det) > ep);
	if (!ok) {
		return ret_mat();
	}

	const auto det_inv = value_type(1) / det;

	const auto m11 = c1*det_inv;
	const auto m12 = -static_cast<value_type>(m.value(0, 1)*m.value(2, 2) - m.value(0, 2)*m.value(2, 1))*det_inv;
	const auto m13 = static_cast<value_type>(m.value(0, 1)*m.value(1, 2) - m.value(0, 2)*m.value(1, 1))*det_inv;
	const auto m21 = c2*det_inv;
	const auto m22 = static_cast<value_type>(m.value(0, 0)*m.value(2, 2) - m.value(0, 2)*m.value(2, 0))*det_inv;
	const auto m23 = -static_cast<value_type>(m.value(0, 0)*m.value(1, 2) - m.value(0, 2)*m.value(1, 0))*det_inv;
	const auto m31 = c0*det_inv;
	const auto m32 = -static_cast<value_type>(m.value(0, 0)*m.value(2, 1) - m.value(0, 1)*m.value(2, 0))*det_inv;
	const auto m33 = static_cast<value_type>(m.value(0, 0)*m.value(1, 1) - m.value(0, 1)*m.value(1, 0))*det_inv;

	return ret_mat{m11, m12, m13, m21, m22, m23, m31, m32, m33};
}

template<class Mat>
auto
matrix_inverse4(const Mat& m, bool& ok, typename Mat::value_type ep) noexcept
{
	using value_type = std::conditional_t<std::is_integral_v<typename Mat::value_type>,
		make_real_t<typename Mat::value_type>,
		typename Mat::value_type>;

	using ret_mat = typename matrix_traits<Mat>::template rebind<value_type, 4, 4, Mat::options>;

	const auto s0 = static_cast<value_type>(m.value(0, 0)*m.value(1, 1) - m.value(1, 0)*m.value(0, 1));
	const auto s1 = static_cast<value_type>(m.value(0, 0)*m.value(1, 2) - m.value(1, 0)*m.value(0, 2));
	const auto s2 = static_cast<value_type>(m.value(0, 0)*m.value(1, 3) - m.value(1, 0)*m.value(0, 3));
	const auto s3 = static_cast<value_type>(m.value(0, 1)*m.value(1, 2) - m.value(1, 1)*m.value(0, 2));
	const auto s4 = static_cast<value_type>(m.value(0, 1)*m.value(1, 3) - m.value(1, 1)*m.value(0, 3));
	const auto s5 = static_cast<value_type>(m.value(0, 2)*m.value(1, 3) - m.value(1, 2)*m.value(0, 3));

	const auto c0 = static_cast<value_type>(m.value(2, 0)*m.value(3, 1) - m.value(3, 0)*m.value(2, 1));
	const auto c1 = static_cast<value_type>(m.value(2, 0)*m.value(3, 2) - m.value(3, 0)*m.value(2, 2));
	const auto c2 = static_cast<value_type>(m.value(2, 0)*m.value(3, 3) - m.value(3, 0)*m.value(2, 3));
	const auto c3 = static_cast<value_type>(m.value(2, 1)*m.value(3, 2) - m.value(3, 1)*m.value(2, 2));
	const auto c4 = static_cast<value_type>(m.value(2, 1)*m.value(3, 3) - m.value(3, 1)*m.value(2, 3));
	const auto c5 = static_cast<value_type>(m.value(2, 2)*m.value(3, 3) - m.value(3, 2)*m.value(2, 3));

	const auto det = s0*c5 - s1*c4 + s2*c3 + s3*c2 - s4*c1 + s5*c0;

	ok = (std::abs(det) > ep);
	if (!ok) {
		return ret_mat();
	}

	const auto det_inv = value_type(1) / det;

	const auto m11 = ( m.value(1, 1)*c5 - m.value(1, 2)*c4 + m.value(1, 3)*c3)*det_inv;
	const auto m12 = (-m.value(0, 1)*c5 + m.value(0, 2)*c4 - m.value(0, 3)*c3)*det_inv;
	const auto m13 = ( m.value(3, 1)*s5 - m.value(3, 2)*s4 + m.value(3, 3)*s3)*det_inv;
	const auto m14 = (-m.value(2, 1)*s5 + m.value(2, 2)*s4 - m.value(2, 3)*s3)*det_inv;
	const auto m21 = (-m.value(1, 0)*c5 + m.value(1, 2)*c2 - m.value(1, 3)*c1)*det_inv;
	const auto m22 = ( m.value(0, 0)*c5 - m.value(0, 2)*c2 + m.value(0, 3)*c1)*det_inv;
	const auto m23 = (-m.value(3, 0)*s5 + m.value(3, 2)*s2 - m.value(3, 3)*s1)*det_inv;
	const auto m24 = ( m.value(2, 0)*s5 - m.value(2, 2)*s2 + m.value(2, 3)*s1)*det_inv;
	const auto m31 = ( m.value(1, 0)*c4 - m.value(1, 1)*c2 + m.value(1, 3)*c0)*det_inv;
	const auto m32 = (-m.value(0, 0)*c4 + m.value(0, 1)*c2 - m.value(0, 3)*c0)*det_inv;
	const auto m33 = ( m.value(3, 0)*s4 - m.value(3, 1)*s2 + m.value(3, 3)*s0)*det_inv;
	const auto m34 = (-m.value(2, 0)*s4 + m.value(2, 1)*s2 - m.value(2, 3)*s0)*det_inv;
	const auto m41 = (-m.value(1, 0)*c3 + m.value(1, 1)*c1 - m.value(1, 2)*c0)*det_inv;
	const auto m42 = ( m.value(0, 0)*c3 - m.value(0, 1)*c1 + m.value(0, 2)*c0)*det_inv;
	const auto m43 = (-m.value(3, 0)*s3 + m.value(3, 1)*s1 - m.value(3, 2)*s0)*det_inv;
	const auto m44 = ( m.value(2, 0)*s3 - m.value(2, 1)*s1 + m.value(2, 2)*s0)*det_inv;

	return ret_mat{m11, m12, m13, m14, m21, m22, m23, m24, m31, m32, m33, m34, m41, m42, m43, m44};
}

template<class Mat>
auto
matrix_inverse(const Mat& m, typename Mat::value_type ep)
{
	constexpr auto dim = std::decay_t<Mat>::dimension;
	const auto inverse = [&m, ep](bool &ok) {
		if constexpr (dim == 2)
			return impl_linalg::matrix_inverse2(m, ok, ep);
		else if constexpr (dim == 3)
			return impl_linalg::matrix_inverse3(m, ok, ep);
		else if constexpr (dim == 4)
			return impl_linalg::matrix_inverse4(m, ok, ep);
		else
			MTK_ASSERT(false);
	};

	bool ok = false;
	using opt = std::optional<decltype(inverse(ok))>;
	opt ret = inverse(ok);
	if (!ok)
		ret = std::nullopt;

	return ret;
}

} // namespace impl_linalg
} // namespace mtk

#endif
