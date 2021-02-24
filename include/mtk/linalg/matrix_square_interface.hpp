#ifndef MTK_LINALG_MATRIX_SQUARE_INTERFACE_HPP
#define MTK_LINALG_MATRIX_SQUARE_INTERACE_HPP

//! @file
//! Contains the matrix_square_interface definition.

#include <mtk/linalg/matrix_interface.hpp>

#ifndef MTK_DOXYGEN
	#include <../src/mtk/linalg/matrix_det_and_inv.hpp>
#endif

#include <optional>
#include <cmath>

namespace mtk {
namespace impl_linalg {
template<class Derived>
struct matrix_no_det_or_inv { };
template<class Derived>
struct matrix_only_det
{
	constexpr auto determinant() const { return impl_linalg::matrix_determinant(static_cast<const Derived&>(*this)); }
};
template<class Derived>
struct matrix_det_and_inv :
	matrix_only_det<Derived>
{
	using _ep_type = typename matrix_traits<Derived>::value_type;

	auto inverted(_ep_type ep = std::numeric_limits<_ep_type>::epsilon()) const { return impl_linalg::matrix_inverse(static_cast<const Derived&>(*this), ep); }
	void invert(_ep_type ep = std::numeric_limits<_ep_type>::epsilon())
	{
		auto inv = this->inverted(ep);
		MTK_PRECOND_LOW(inv);
		static_cast<Derived&>(*this) = std::move(*inv);
	}
	bool is_invertible(_ep_type ep = std::numeric_limits<_ep_type>::epsilon()) const { return (std::abs(this->determinant()) > ep); }
};
template<class Derived>
struct matrix_sqiface_base
{
	using value_type = std::decay_t<typename matrix_traits<Derived>::value_type>;

	static constexpr auto dim = matrix_traits<Derived>::row_dimension;
	static constexpr bool is_complex = std::is_same_v<value_type, std::complex<make_real_t<value_type>>>;
	using type = std::conditional_t<(dim >= 2) && (dim <= 4) && !is_complex,
		std::conditional_t<std::is_floating_point_v<value_type>,
			matrix_det_and_inv<Derived>,
			matrix_only_det<Derived>>,
		matrix_no_det_or_inv<Derived>>;
};
} // namespace impl_linalg



//! @defgroup mat_sq_iface mtk/linalg/matrix_square_interface.hpp
//! @{

//! @brief CRTP class which defines the basic interface for square matrices.
//!
//! @pre Derived must be the most derived type.
//! @pre mtk::matrix_traits must be specialized for Derived.
//! @pre The scalar type of Derived must be either a signed integral type,
//! a floating point type, or a std::complex<> type.
//! @pre The rows and columns of a square matrix must be equal.
template<class Derived>
class matrix_square_interface :
	public matrix_interface<Derived>
#ifndef MTK_DOXYGEN
	,public impl_linalg::matrix_sqiface_base<Derived>::type
#endif
{
public:
	using _base = matrix_interface<Derived>;
	using typename _base::value_type;
	using typename _base::size_type;
	using typename _base::iterator;
	using typename _base::const_iterator;
	using _base::row_dimension;
	using _base::column_dimension;
	using _base::options;

	//! The compile time dimension of the square matrix.
	static constexpr
	size_type
	dimension = (row_dimension == dynamic_dimension ? column_dimension : row_dimension);

	static constexpr
	bool
	_is_complex = std::is_same_v<value_type, std::complex<make_real_t<value_type>>>;

	//! Returns the order of the matrix.
	constexpr
	size_type
	order() const
	{
		MTK_PRECOND_LOW(this->rows() == this->columns());
		if constexpr (row_dimension == dynamic_dimension)
			return this->columns();
		else
			return this->rows();
	}

	//! Returns the diagonal of the matrix.
	constexpr
	auto
	diagonal()
	{
		using iter = impl_linalg::step_iterator<iterator>;
		using const_iter = impl_linalg::step_iterator<const_iterator>;
		using ret_type = impl_linalg::matrix_vector_reference<iter, const_iter, dimension, 1, options>;
		return ret_type(iter(this->begin(), 0, this->order() + 1), this->order(), 1);
	}

	//! @copydoc diagonal()
	constexpr
	auto
	diagonal() const
	{
		using iter = impl_linalg::step_iterator<const_iterator>;
		using const_iter = impl_linalg::step_iterator<const_iterator>;
		using ret_type = impl_linalg::matrix_vector_reference<iter, const_iter, dimension, 1, options>;
		return ret_type(iter(this->begin(), 0, this->order() + 1), this->order(), 1);
	}

	//! @brief Returns true if the matrix is the identity matrix,
	//! else false.
	constexpr
	bool
	is_identity() const
	{
		const auto order = this->order();
		auto it = this->begin();
		for (size_type i = 0; i < order; ++i) {
			for (size_type j = 0; j < order; ++j) {
				const auto cmp = (i == j ? value_type(1) : value_type());
				if (*(it++) != cmp)
					return false;
			}
		}
		return true;
	}

	//! @brief Returns true if the matrix is a diagonal matrix,
	//! else false.
	constexpr
	bool
	is_diagonal() const
	{
		const auto order = this->order();
		auto it = this->begin();
		for (size_type i = 0; i < order; ++i) {
			for (size_type j = 0; j < order; ++j) {
				const bool is_off_diagonal = (i != j);
				const bool is_zero = (*(it++) == value_type());
				if (is_off_diagonal && !is_zero)
					return false;
			}
		}
		return true;
	}

	//! @brief Returns true if the matrix is a symmetric matrix,
	//! else false.
	constexpr
	bool
	is_symmetric() const
	{
		const auto order = this->order();
		for (size_type i = 1; i < order; ++i) {
			for (size_type j = 0; j < i; ++j) {
				if (this->value(i, j) != this->value(j, i))
					return false;
			}
		}
		return true;
	}

	//! @brief Returns true if the matrix is a skew-symmetric matrix,
	//! else false.
	constexpr
	bool
	is_skew_symmetric() const
	{
		const auto order = this->order();
		for (size_type i = 1; i < order; ++i) {
			for (size_type j = 0; j < i; ++j) {
				if (this->value(i, j) != -this->value(j, i))
					return false;
			}
		}
		return true;
	}

	//! @brief Returns true if the matrix is an hermetian matrix,
	//! else false.
	constexpr
	bool
	is_hermetian() const
	{
		if constexpr (!_is_complex) {
			return this->is_symmetric();
		} else {
			const auto order = this->order();
			for (size_type i = 1; i < order; ++i) {
				for (size_type j = 0; j < i; ++j) {
					if (this->value(i, j) != std::conj(this->value(j, i)))
						return false;
				}
			}
			return true;
		}
	}

	//! Returns the trace of the matrix.
	constexpr
	value_type
	trace() const
	{
		value_type ret = value_type();
		for (auto el : this->diagonal()) {
			ret += el;
		}
		return ret;
	}

	//! Sets the matrix to identity.
	constexpr
	void
	to_identity()
	{
		const auto order = this->order();
		auto it = this->begin();
		for (size_type i = 0; i < order; ++i) {
			for (size_type j = 0; j < order; ++j) {
				const auto val = (i == j ? value_type(1) : value_type());
				*(it++) = val;
			}
		}
	}

	//! Sets the matrix to its transpose.
	constexpr
	void
	transpose()
	{
		const auto order = this->order();
		for (size_type i = 1; i < order; ++i) {
			for (size_type j = 0; j < i; ++j) {
				std::swap(this->value(i, j), this->value(j, i));
			}
		}
	}

#ifdef MTK_DOXYGEN
	//! @brief Returns the determinant of the matrix.
	//!
	//! @note This function is only available for non-complex square matrices with
	//! dimensions 2, 3, and 4.
	constexpr
	value_type
	determinant() const;

	//! @brief Returns the inverse of the matrix if it exists, else
	//! std::nullopt.
	//!
	//! The matrix is invertible if the absolute value of the determinant
	//! is larger than the given epsilon.
	//!
	//! @note This function is only available for floating-point square matrices with
	//! dimensions 2, 3, and 4.
	std::optional<matrix<value_type, dimension, dimension, options>>
	inverted(value_type ep = std::numeric_limits<value_type>::epsilon()) const;

	//! @brief Sets the matrix to its inverse.
	//!
	//! @note This function is only available for floating-point square matrices with
	//! dimensions 2, 3, and 4.
	//!
	//! @pre The matrix must be invertible.
	//!
	//! @note The matrix is invertible if the absolute value of the determinant
	//! is larger than the given epsilon.
	void
	invert(value_type ep = std::numeric_limits<value_type>::epsilon());

	//! @brief Returns true if the absolute value of the determinant is
	//! larger than epsilon, else false.
	//!
	//! @note This function is only available for floating-point square matrices with
	//! dimensions 2, 3, and 4.
	bool
	is_invertible(value_type ep = std::numeric_limits<value_type>::epsilon()) const;
#endif
};

//! @}

} // namespace mtk

#endif
