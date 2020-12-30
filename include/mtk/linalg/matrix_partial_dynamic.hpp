#ifndef MTK_LINALG_MATRIX_PARTIAL_DYNAMIC_HPP
#define MTK_LINALG_MATRIX_PARTIAL_DYNAMIC_HPP

//! @file
//! Contains the matrix definition for partially dynamic matrices.

#include <mtk/linalg/matrix_base.hpp>

#include <initializer_list>
#include <memory>

namespace mtk {

//! @defgroup mat_part mtk/linalg/matrix_partial_dynamic.hpp
//! @{

template<class S
	,size_t Columns
	,matrix_options Opt>
struct matrix_traits<matrix<S, dynamic_dimension, Columns, Opt>>
{
	using _mat = matrix<S, dynamic_dimension, Columns, Opt>;

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
	column_dimension = Columns;

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
	columns(const _mat&)
	{
		return Columns;
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
		return (m.m_data.get() + m.m_rows*Columns);
	}

	static constexpr
	const_iterator
	end(const _mat& m)
	{
		return (m.m_data.get() + m.m_rows*Columns);
	}
};

template<class S
	,size_t Rows
	,matrix_options Opt>
struct matrix_traits<matrix<S, Rows, dynamic_dimension, Opt>>
{
	using _mat = matrix<S, Rows, dynamic_dimension, Opt>;

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
	row_dimension = Rows;

	static constexpr
	size_t
	column_dimension = dynamic_dimension;

	static constexpr
	matrix_options
	options = Opt;

	static constexpr
	size_t
	rows(const _mat&)
	{
		return Rows;
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
		return (m.m_data.get() + Rows*m.m_cols);
	}

	static constexpr
	const_iterator
	end(const _mat& m)
	{
		return (m.m_data.get() + Rows*m.m_cols);
	}
};



//! @copydoc mtk::matrix
template<class Scalar
	,size_t Columns
	,matrix_options Options>
class matrix<Scalar, dynamic_dimension, Columns, Options> :
	public matrix_base<matrix<Scalar, dynamic_dimension, Columns, Options>>
{
public:
	//! Initializes the matrix to the empty matrix.
	constexpr
	matrix() :
		m_data(nullptr),
		m_rows(0)
	{ }

	//! @brief Initializes the matrix to a rows*Columns matrix with elements
	//! initialized to zero.
	matrix(size_t rows) :
		m_data(rows == 0 ? nullptr : std::make_unique<Scalar[]>(rows*Columns)),
		m_rows(rows)
	{ }

	//! @brief Initializes the matrix to a args.size() / Columns matrix with elements
	//! initialized to the given args in a row-major order.
	//!
	//! @pre The number of args must be an integer multiple of Columns.
	matrix(std::initializer_list<Scalar> args) :
		matrix(args.size() / Columns)
	{
		MTK_IMPL_LIB_ASSERT(args.size() == m_rows*Columns);
		this->_raw_assign(args.begin());
	}

	//! @brief Initializes the matrix to a std::distance(first, last) / Columns matrix with elements
	//! initialized to the given range in a row-major order.
	//!
	//! @pre InputIter must be an input iterator.
	//! @pre The value_type of the iterator must be convertible to Scalar.
	//! @pre The number of values in the given range must be an integer
	//! multiple of Columns
	template<class ForwardIter
#ifndef MTK_DOXYGEN
		,require<is_forward_iterator_v<ForwardIter>> = 0
#endif
	>
	matrix(ForwardIter first, ForwardIter last) :
		matrix(std::distance(first, last) / Columns)
	{
		MTK_IGNORE(last);
		MTK_IMPL_LIB_ASSERT(std::distance(first, last) == m_rows*Columns);

		this->_raw_assign(first);
	}

	matrix(const matrix& other) :
		matrix(other.m_rows)
	{
		this->_raw_assign(other);
	}

	matrix(matrix&& other) noexcept :
		m_data(std::exchange(other.m_data, nullptr)),
		m_rows(std::exchange(other.m_rows, 0))
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
		matrix(other.rows()*other.columns() / Columns)
	{
		this->_raw_assign(other);
	}

	~matrix() = default;

	matrix&
	operator=(const matrix& rhs)
	{
		if (m_rows == rhs.m_rows)
			this->_raw_assign(rhs);
		else
			*this = matrix(rhs);

		return *this;
	}

	matrix
	operator=(matrix&& rhs) noexcept
	{
		matrix tmp(std::move(*this));

		std::swap(rhs.m_data, m_data);
		std::swap(rhs.m_rows, m_rows);

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
		if (this->size() == rhs.size())
			this->_raw_assign(rhs);
		else
			*this = matrix(rhs);

		return *this;
	}

private:
	friend matrix_traits<matrix>;

	std::unique_ptr<Scalar[]> m_data;
	size_t m_rows;
};



//! @copydoc mtk::matrix
template<class Scalar
	,size_t Rows
	,matrix_options Options>
class matrix<Scalar, Rows, dynamic_dimension, Options> :
	public matrix_base<matrix<Scalar, Rows, dynamic_dimension, Options>>
{
public:
	//! Initializes the matrix to the empty matrix.
	constexpr
	matrix() :
		m_data(nullptr),
		m_cols(0)
	{ }

	//! @brief Initializes the matrix to a rows*Columns matrix with elements
	//! initialized to zero.
	matrix(size_t cols) :
		m_data(cols == 0 ? nullptr : std::make_unique<Scalar[]>(cols*Rows)),
		m_cols(cols)
	{ }

	//! @brief Initializes the matrix to a args.size() / Rows matrix with elements
	//! initialized to the given args in a row-major order.
	//!
	//! @pre The number of args must be an integer multiple of Rows.
	matrix(std::initializer_list<Scalar> args) :
		matrix(args.size() / Rows)
	{
		MTK_IMPL_LIB_ASSERT(args.size() == m_cols*Rows);
		this->_raw_assign(args.begin());
	}

	//! @brief Initializes the matrix to a std::distance(first, last) / Rows matrix with elements
	//! initialized to the given range in a row-major order.
	//!
	//! @pre InputIter must be an input iterator.
	//! @pre The value_type of the iterator must be convertible to Scalar.
	//! @pre The number of values in the given range must be an integer
	//! multiple of Rows
	template<class ForwardIter
#ifndef MTK_DOXYGEN
		,require<is_forward_iterator_v<ForwardIter>> = 0
#endif
	>
	matrix(ForwardIter first, ForwardIter last) :
		matrix(std::distance(first, last) / Rows)
	{
		MTK_IGNORE(last);
		MTK_IMPL_LIB_ASSERT(std::distance(first, last) == m_cols*Rows);

		this->_raw_assign(first);
	}

	matrix(const matrix& other) :
		matrix(other.m_cols)
	{
		this->_raw_assign(other);
	}

	matrix(matrix&& other) noexcept :
		m_data(std::exchange(other.m_data, nullptr)),
		m_cols(std::exchange(other.m_cols, 0))
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
		matrix(other.rows()*other.columns() / Rows)
	{
		this->_raw_assign(other);
	}

	~matrix() = default;

	matrix&
	operator=(const matrix& rhs)
	{
		if (m_cols == rhs.m_cols)
			this->_raw_assign(rhs);
		else
			*this = matrix(rhs);

		return *this;
	}

	matrix
	operator=(matrix&& rhs) noexcept
	{
		matrix tmp(std::move(*this));

		std::swap(rhs.m_data, m_data);
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
		if (this->size() == rhs.size())
			this->_raw_assign(rhs);
		else
			*this = matrix(rhs);

		return *this;
	}

private:
	friend matrix_traits<matrix>;

	std::unique_ptr<Scalar[]> m_data;
	size_t m_cols;
};

//! @}

} // namespace mtk

#endif
