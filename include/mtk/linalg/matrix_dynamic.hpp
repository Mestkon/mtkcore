#ifndef MTK_LINALG_MATRIX_HPP
#define MTK_LINALG_MATRIX_HPP

//! @file
//! Contains the matrix definition for dynamic matrices.

#include <mtk/linalg/matrix_base.hpp>

#include <initializer_list>
#include <memory>

namespace mtk {

//! @defgroup mat_dyn mtk/linalg/matrix_dynamic.hpp
//! @{

template<class S
	,matrix_options Opt>
struct matrix_traits<matrix<S, dynamic_dimension, dynamic_dimension, Opt>>
{
	using _mat = matrix<S, dynamic_dimension, dynamic_dimension, Opt>;

	using value_type = S;
	using iterator = S*;
	using const_iterator = const S*;

	template<class Sca
		,size_t Ro
		,size_t Co
		,matrix_options Options>
	using rebind = matrix<Sca, Ro, Co, Options>;

	static constexpr
	size_t
	row_dimension = dynamic_dimension;

	static constexpr
	size_t
	column_dimension = dynamic_dimension;

	static constexpr
	matrix_options
	options = Opt;

	static constexpr
	size_t
	rows(const _mat& m)
	{
		return m.m_rows;
	}

	static constexpr
	size_t
	columns(const _mat& m)
	{
		return m.m_cols;
	}

	static constexpr
	iterator
	begin(_mat& m)
	{
		return m.m_data.get();
	}

	static constexpr
	const_iterator
	begin(const _mat& m)
	{
		return m.m_data.get();
	}

	static constexpr
	iterator
	end(_mat& m)
	{
		return (m.m_data.get() + m.m_rows*m.m_cols);
	}

	static constexpr
	const_iterator
	end(const _mat& m)
	{
		return (m.m_data.get() + m.m_rows*m.m_cols);
	}
};



//! @copydoc mtk::matrix
template<class Scalar
	,matrix_options Options>
class matrix<Scalar, dynamic_dimension, dynamic_dimension, Options> :
	public matrix_base<matrix<Scalar, dynamic_dimension, dynamic_dimension, Options>>
{
public:
	//! Initializes the matrix to the empty matrix.
	constexpr
	matrix() noexcept :
		m_data(nullptr),
		m_rows(0),
		m_cols(0)
	{ }

	//! @brief Initializes the matrix to a rows*cols matrix with elements
	//! initialized to zero.
	matrix(size_t rows, size_t cols) :
		m_data(rows*cols == 0 ? nullptr : std::make_unique<Scalar[]>(rows*cols)),
		m_rows(rows),
		m_cols(cols)
	{ }

	//! @brief Initializes the matrix to a rows*cols matrix with elements
	//! initialized to the given args in a row-major order.
	//!
	//! @pre The number of args must be equal to the number of elements in the matrix.
	matrix(size_t rows, size_t cols, std::initializer_list<Scalar> args) :
		matrix(rows, cols)
	{
		MTK_PRECOND_LOW(args.size() == rows*cols);
		this->_raw_assign(args.begin());
	}

	//! @brief Initializes the matrix to a rows*cols matrix with elements
	//! initialized to the given range in a row-major order.
	//!
	//! @pre InputIter must be an input iterator.
	//! @pre The value_type of the iterator must be convertible to Scalar.
	//! @pre The number of values in the given range must be equal to
	//! the number of elements in the matrix.
	template<class InputIter
#ifndef MTK_DOXYGEN
		,require<is_input_iterator_v<InputIter>> = 0
#endif
	>
	matrix(size_t rows, size_t cols, InputIter first, InputIter last) :
		matrix(rows, cols)
	{
		MTK_IGNORE(last);
		if constexpr (is_forward_iterator_v<InputIter>)
			MTK_PRECOND_LOW(std::distance(first, last) == rows*cols);

		this->_raw_assign(first);
	}

	matrix(const matrix& other) :
		matrix(other.m_rows, other.m_cols)
	{
		this->_raw_assign(other);
	}

	matrix(matrix&& rhs) noexcept :
		m_data(std::exchange(rhs.m_data, nullptr)),
		m_rows(std::exchange(rhs.m_rows, 0)),
		m_cols(std::exchange(rhs.m_cols, 0))
	{ }

	//! @brief Initializes the matrix as a copy of the given matrix.
	//!
	//! @pre The given matrix must have the same value_type, row_dimension,
	//! and column_dimension as the current matrix.
	template<class Other
#ifndef MTK_DOXYGEN
		,require<impl_linalg::is_matrix_similar<matrix, Other>::value> = 0
#endif
	>
	matrix(const matrix_interface<Other>& other) :
		matrix(other.rows(), other.columns())
	{
		this->_raw_assign(other);
	}

	~matrix() = default;

	matrix&
	operator=(const matrix& rhs)
	{
		if ((m_rows == rhs.m_rows) && (m_cols == rhs.m_cols))
			this->_raw_assign(rhs);
		else
			*this = matrix(rhs);

		return *this;
	}

	matrix&
	operator=(matrix&& rhs) noexcept
	{
		matrix tmp(std::move(*this));

		std::swap(rhs.m_data, m_data);
		std::swap(rhs.m_rows, m_rows);
		std::swap(rhs.m_cols, m_cols);

		return *this;
	}

	//! @brief Copies the given matrix into the current matrix.
	//!
	//! @pre The given matrix must have the same value_type, row_dimension,
	//! and column_dimension as the current matrix.
	template<class Other
#ifndef MTK_DOXYGEN
		,require<impl_linalg::is_matrix_similar<matrix, Other>::value> = 0
#endif
	>
	matrix&
	operator=(const matrix_interface<Other>& rhs)
	{
		if ((m_rows == rhs.rows()) && (m_cols == rhs.columns()))
			this->_raw_assign(rhs);
		else
			*this = matrix(rhs);

		return *this;
	}

private:
	friend matrix_traits<matrix>;

	std::unique_ptr<Scalar[]> m_data;
	size_t m_rows;
	size_t m_cols;
};

//! @}

} // namespace mtk

#endif
