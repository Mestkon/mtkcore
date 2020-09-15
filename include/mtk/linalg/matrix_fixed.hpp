#ifndef MTK_LINALG_MATRIX_FIXED_HPP
#define MTK_LINALG_MATRIX_FIXED_HPP

//! @file
//! Contains the matrix definition for fixed size matrices.

#include <mtk/linalg/matrix_base.hpp>

#include <initializer_list>

namespace mtk {

//! @defgroup mat_fix mtk/linalg/matrix_fixed.hpp
//! @{

template<class S
	,size_t R
	,size_t C
	,matrix_options Opt>
struct matrix_traits<matrix<S, R, C, Opt>>
{
	static_assert(R != dynamic_dimension);
	static_assert(C != dynamic_dimension);

	using _mat = matrix<S, R, C, Opt>;

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
	row_dimension = R;

	static constexpr
	size_t
	column_dimension = C;

	static constexpr
	matrix_options
	options = Opt;

	static constexpr
	size_t
	rows(const _mat&)
	{
		return R;
	}

	static constexpr
	size_t
	columns(const _mat&)
	{
		return C;
	}

	static constexpr
	iterator
	begin(_mat& m)
	{
		return std::begin(m.m_data);
	}

	static constexpr
	const_iterator
	begin(const _mat& m)
	{
		return std::begin(m.m_data);
	}

	static constexpr
	iterator
	end(_mat& m)
	{
		return std::end(m.m_data);
	}

	static constexpr
	const_iterator
	end(const _mat& m)
	{
		return std::end(m.m_data);
	}
};



//! @brief Class representing a mathematical matrix.
//!
//! The general implementation is for fixed matrices.
//! Use mtk::dynamic_dimension as Rows and/or Columns
//! if a dynamic nature is required.
//! - mtk::matrix
//!
//! For dynamic matrices check the specializations:
//!	- matrix<Scalar, dynamic_dimension, Columns, Options>
//! - matrix<Scalar, Rows, dynamic_dimension, Options>
//! - matrix<Scalar, dynamic_dimension, dynamic_dimension, Options>
//!
//! @tparam Scalar Type representing a scalar.
//! @tparam Rows The number of rows in the matrix.
//! @tparam Columns The number of columns in the matrix.
//! @tparam Options The configuration of the matrix.
//!
//! @pre Scalar must be either a signed integral type,
//! a floating point type, or a std::complex<> type.
//!
//! @sa mat_base
//! @sa matrix_square_interface
//! @sa vector_interface
//! @sa matrix_interface
template<class Scalar
	,size_t Rows
	,size_t Columns
	,matrix_options Options>
class matrix :
	public matrix_base<matrix<Scalar, Rows, Columns, Options>>
{
public:
	static_assert(Rows != dynamic_dimension);
	static_assert(Columns != dynamic_dimension);

	//! Initializes all elements to zero.
	constexpr
	matrix() :
		m_data{}
	{ }

	//! @brief Initializes the elements to the given arguments in
	//! a row-major order.
	//!
	//! @pre Args must be convertible to Scalar.
	//! @pre The number of args must be equal to the number of elements in the matrix.
	template<class... Args
#ifndef MTK_DOXYGEN
		,bool IsRm = !matrix::_is_column_major
		,require<IsRm> = 0
		,require<(sizeof...(Args) != 0)> = 0
		,require<(sizeof...(Args) == Rows*Columns)> = 0
		,require<(std::is_convertible_v<Args, Scalar> && ...)> = 0
#endif
	>
	constexpr
	matrix(Args&&... args) :
		m_data{static_cast<Scalar>(std::forward<Args>(args))...}
	{ }

#ifndef MTK_DOXYGEN
		template<class... Args
		,bool IsRm = !matrix::_is_column_major
		,require<!IsRm> = 0
		,require<(sizeof...(Args) != 0)> = 0
		,require<(sizeof...(Args) == Rows*Columns)> = 0
		,require<(std::is_convertible_v<Args, Scalar> && ...)> = 0
	>
	constexpr
	matrix(Args&&... args) :
		matrix()
	{
		auto ilist = {static_cast<Scalar>(std::forward<Args>(args))...};
		this->_raw_assign(ilist.begin());
	}
#endif

	//! @brief Initializes the elements to the given range in
	//! a row-major order.
	//!
	//! @pre InputIter must be an input iterator.
	//! @pre The value_type of the iterator must be convertible to Scalar.
	//! @pre The number of values in the given range must be equal to
	//! the number of elements in the matrix.
	template<class InputIter
#ifndef MTK_DOXYGEN
		,require<is_input_iterator_v<InputIter>> = 0
		,require<std::is_convertible_v<iter::value<InputIter>, Scalar>> = 0
#endif
	>
	constexpr
	matrix(InputIter first, InputIter last) :
		matrix()
	{
		MTK_IGNORE(last);
		if constexpr (is_forward_iterator_v<InputIter>)
			MTK_IMPL_LIB_ASSERT(std::distance(first, last) == Rows*Columns);

		this->_raw_assign(first);
	}

	//! @brief Initializes the matrix as a copy of the given matrix.
	//!
	//! @pre The given matrix must have the same value_type, row_dimension,
	//! and column_dimension as the current matrix.
	template<class Other
#ifndef MTK_DOXYGEN
		,require<impl_linalg::is_matrix_similar<matrix, Other>::value> = 0
#endif
	>
	constexpr
	matrix(const matrix_interface<Other>& other) :
		matrix()
	{
		this->_raw_assign(other);
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
	constexpr
	matrix&
	operator=(const matrix_interface<Other>& rhs)
	{
		this->_raw_assign(rhs);
		return *this;
	}

private:
	friend matrix_traits<matrix>;

	Scalar m_data[Rows*Columns + (Rows*Columns == 0)];
};

//! @}

} // namespace mtk

#endif
