#ifndef MTK_LINALG_MATRIX_INTERFACE_HPP
#define MTK_LINALG_MATRIX_INTERFACE_HPP

//! @file
//! Contains the matrix_interface definition.

#include <mtk/linalg/matrix_container_interface.hpp>

#include <mtk/core/iterator_traits.hpp>

#include <complex>

namespace mtk {
namespace impl_linalg {
template<class Derived>
struct matrix_no_iface_base { };
template<class Derived>
struct matrix_data_func
{
	constexpr auto data() { return static_cast<Derived&>(*this).begin(); }
	constexpr auto data() const { return static_cast<const Derived&>(*this).begin(); }
};
template<class Derived>
struct matrix_iface_base
{
	using type = std::conditional_t<std::is_pointer_v<typename matrix_traits<Derived>::iterator>,
		impl_linalg::matrix_data_func<Derived>,
		impl_linalg::matrix_no_iface_base<Derived>>;
};
} // namespace impl_linalg

//! @defgroup mat_iface mtk/linalg/matrix_interface.hpp
//! @{

//! @brief CRTP class which defines the basic interface for matrices.
//!
//! @pre Derived must be the most derived type.
//! @pre mtk::matrix_traits must be specialized for Derived.
//! @pre The scalar type of Derived must be either a signed integral type,
//! a floating point type, or a std::complex<> type.
template<class Derived>
class matrix_interface :
	public matrix_container_interface<Derived>
#ifndef MTK_DOXYGEN
	,public impl_linalg::matrix_iface_base<Derived>::type
#endif
{
public:
	using _base = matrix_container_interface<Derived>;
	using typename _base::value_type;
	using typename _base::size_type;
	using typename _base::reference;
	using typename _base::const_reference;
	using typename _base::pointer;
	using typename _base::const_pointer;
	using typename _base::iterator;
	using typename _base::const_iterator;
	using _base::row_dimension;
	using _base::column_dimension;
	using _base::options;

	//! @brief Iterator type to iterate over the rows of a matrix.
	//!
	//! The iterator formally conforms to the input_iterator named requirement and
	//! therefore uses std::input_iterator_tag, but supports all the requirements of
	//! a random_access_iterator named requirement except for the requirement that the
	//! std::iterator_traits<>::reference is not an actual reference.
	using row_iterator = impl_linalg::matrix_vector_iterator<iterator, const_iterator, row_dimension, column_dimension, options, true>;
	//! @copydoc row_iterator
	using const_row_iterator = impl_linalg::matrix_vector_iterator<const_iterator, const_iterator, row_dimension, column_dimension, options, true>;
	//! @brief Iterator type to iterate over the columns of a matrix.
	//!
	//! The iterator formally conforms to the input_iterator named requirement and
	//! therefore uses std::input_iterator_tag, but supports all the requirements of
	//! a random_access_iterator named requirement except for the requirement that the
	//! std::iterator_traits<>::reference is not an actual reference.
	using column_iterator = impl_linalg::matrix_vector_iterator<iterator, const_iterator, row_dimension, column_dimension, options, false>;
	//! @copydoc column_iterator
	using const_column_iterator = impl_linalg::matrix_vector_iterator<const_iterator, const_iterator, row_dimension, column_dimension, options, false>;

	static constexpr
	bool
	_is_vector = (row_dimension == 1) || (column_dimension == 1);

	static constexpr
	bool
	_is_column_major = ((options & matrix_options::column_major) == matrix_options::column_major);

	static_assert((std::is_integral_v<value_type> && std::is_signed_v<value_type>) ||
		std::is_floating_point_v<value_type> ||
		std::is_same_v<value_type, std::complex<float>> ||
		std::is_same_v<value_type, std::complex<double>> ||
		std::is_same_v<value_type, std::complex<ldouble>>,
		"The scalar type of mtk::matrix_interface must be a signed integer type, "
		"a floating point type or a std::complex type");



	//! Returns an iterator to the beginning row of the matrix.
	constexpr
	row_iterator
	begin_rows()
	{
		return row_iterator(this->begin(), this->rows(), this->columns(), 0);
	}

	//! @copydoc begin_rows()
	constexpr
	const_row_iterator
	begin_rows() const
	{
		return const_row_iterator(this->begin(), this->rows(), this->columns(), 0);
	}

	//! @copydoc begin_rows()
	constexpr
	const_row_iterator
	cbegin_rows() const
	{
		return this->begin_rows();
	}

	//! Returns an iterator to the end row of the matrix.
	constexpr
	row_iterator
	end_rows()
	{
		return row_iterator(this->begin(), this->rows(), this->columns(), this->rows());
	}

	//! @copydoc end_rows()
	constexpr
	const_row_iterator
	end_rows() const
	{
		return const_row_iterator(this->begin(), this->rows(), this->columns(), this->rows());
	}

	//! @copydoc end_rows()
	constexpr
	const_row_iterator
	cend_rows() const
	{
		return this->end_rows();
	}

	//! Returns an iterator to the beginning column of the matrix.
	constexpr
	column_iterator
	begin_columns()
	{
		return column_iterator(this->begin(), this->rows(), this->columns(), 0);
	}

	//! @copydoc begin_columns()
	constexpr
	const_column_iterator
	begin_columns() const
	{
		return const_column_iterator(this->begin(), this->rows(), this->columns(), 0);
	}

	//! @copydoc begin_columns()
	constexpr
	const_column_iterator
	cbegin_columns() const
	{
		return this->begin_columns();
	}

	//! Returns an iterator to the end column of the matrix.
	constexpr
	column_iterator
	end_columns()
	{
		return column_iterator(this->begin(), this->rows(), this->columns(), this->columns());
	}

	//! @copydoc end_columns()
	constexpr
	const_column_iterator
	end_columns() const
	{
		return const_column_iterator(this->begin(), this->rows(), this->columns(), this->columns());
	}

	//! @copydoc end_columns()
	constexpr
	const_column_iterator
	cend_columns() const
	{
		return this->end_columns();
	}



	//! @brief Returns a reference type to the given row.
	//!
	//! @pre idx must be smaller than the number of rows in the matrix.
	constexpr
	auto
	row(size_type idx)
	{
		MTK_PRECOND_LOW(idx < this->rows());
		return *(this->begin_rows() + idx);
	}

	//! @copydoc row(size_type)
	constexpr
	auto
	row(size_type idx) const
	{
		MTK_PRECOND_LOW(idx < this->rows());
		return *(this->begin_rows() + idx);
	}

	//! @brief Returns a reference type to the given column.
	//!
	//! @pre idx must be smaller than the number of columns in the matrix.
	constexpr
	auto
	column(size_type idx)
	{
		MTK_PRECOND_LOW(idx < this->columns());
		return *(this->begin_columns() + idx);
	}

	//! @copydoc column(size_type)
	constexpr
	auto
	column(size_type idx) const
	{
		MTK_PRECOND_LOW(idx < this->columns());
		return *(this->begin_columns() + idx);
	}


	//! @brief Returns the given row of the matrix.
	//!
	//! If either row_dimension or column_dimension is equal to 1
	//! then it returns the given element instead.
	//!
	//! @brief idx must be a valid index.
#ifndef MTK_DOXYGEN
	template<bool IsVec = _is_vector
		,require<IsVec == _is_vector> = 0
		,require<!IsVec> = 0>
#endif
	constexpr
	auto
	operator[](size_type idx)
	{
		MTK_PRECOND_LOW(idx < this->rows());
		return *(this->begin_rows() + idx);
	}

	//! @copydoc operator[](size_type)
#ifndef MTK_DOXYGEN
	template<bool IsVec = _is_vector
		,require<IsVec == _is_vector> = 0
		,require<!IsVec> = 0>
#endif
	constexpr
	auto
	operator[](size_type idx) const
	{
		MTK_PRECOND_LOW(idx < this->rows());
		return *(this->begin_rows() + idx);
	}

#ifndef MTK_DOXYGEN
	template<bool IsVec = _is_vector
		,require<IsVec == _is_vector> = 0
		,require<IsVec> = 0>
	constexpr
	reference
	operator[](size_type idx)
	{
		MTK_PRECOND_LOW(idx < this->size());
		return *(this->begin() + idx);
	}

	template<bool IsVec = _is_vector
		,require<IsVec == _is_vector> = 0
		,require<IsVec> = 0>
	constexpr
	const_reference
	operator[](size_type idx) const
	{
		MTK_PRECOND_LOW(idx < this->size());
		return *(this->begin() + idx);
	}
#endif



	//! @brief Returns the element at the given row and column.
	//!
	//! @pre row and col must be valid indices.
	constexpr
	reference
	value(size_type row, size_type col)
	{
		MTK_PRECOND_LOW(row < this->rows());
		MTK_PRECOND_LOW(col < this->columns());
		if constexpr (!_is_column_major)
			return *(this->begin() + row*this->columns() + col);
		else
			return *(this->begin() + col*this->rows() + row);
	}

	//! @copydoc value(size_type, size_type)
	constexpr
	const_reference
	value(size_type row, size_type col) const
	{
		MTK_PRECOND_LOW(row < this->rows());
		MTK_PRECOND_LOW(col < this->columns());
		if constexpr (!_is_column_major)
			return *(this->begin() + row*this->columns() + col);
		else
			return *(this->begin() + col*this->rows() + row);
	}

	//! @brief Returns the element at the given index.
	//!
	//! @note This overload is only present for vectors.
	//!
	//! @pre idx must be a valid index.
#ifndef MTK_DOXYGEN
	template<bool IsVec = _is_vector
		,require<IsVec == _is_vector> = 0
		,require<IsVec> = 0>
#endif
	reference
	value(size_type idx)
	{
		MTK_PRECOND_LOW(idx < this->size());
		return *(this->begin() + idx);
	}

	//! @copydoc value(size_type)
#ifndef MTK_DOXYGEN
	template<bool IsVec = _is_vector
		,require<IsVec == _is_vector> = 0
		,require<IsVec> = 0>
#endif
	const_reference
	value(size_type idx) const
	{
		MTK_PRECOND_LOW(idx < this->size());
		return *(this->begin() + idx);
	}


#ifdef MTK_DOXYGEN
	//! @brief Returns a pointer to the underlying data.
	//!
	//! @note This overload is only present if the underlying data
	//! is sequential in memory.
	constexpr
	pointer
	data();

	//! @copydoc data()
	constexpr
	const_pointer
	data() const;
#endif


	//! @brief Returns the transpose of the matrix.
	constexpr
	auto
	transposed() const
	{
		const auto create_mat = [this]() {
			using mat = typename matrix_traits<Derived>::template rebind<value_type, column_dimension, row_dimension, options>;
			if constexpr ((row_dimension == dynamic_dimension) && (column_dimension == dynamic_dimension))
				return mat(this->columns(), this->rows());
			else if constexpr (row_dimension == dynamic_dimension)
				return mat(this->rows());
			else if constexpr (column_dimension == dynamic_dimension)
				return mat(this->columns());
			else
				return mat();
		};

		auto ret = create_mat();
		const auto row_end = ret.cend_rows();
		auto row_it = ret.begin_rows();
		auto col_it = this->begin_columns();
		while (row_it != row_end) {
			*(row_it++) = *(col_it++);
		}
		return ret;
	}

protected:
	template<class Other>
	constexpr
	void
	_raw_assign(const matrix_interface<Other>& other)
	{
		if constexpr ((row_dimension == 1) || (column_dimension == 1)) {
			this->_raw_assign(other.begin());
		} else {
			const auto [p1, p2] = impl_linalg::optimal_range(*this, other);
			const auto vec_end = p1.second;
			auto vec_it = p1.first;
			auto vec_first = p2.first;
			while (vec_it != vec_end) {
				*(vec_it++) = *(vec_first++);
			}
		}
	}

	template<class Iter
		,require<is_iterator_v<Iter>> = 0>
	constexpr
	void
	_raw_assign(Iter first)
	{
		if constexpr (!_is_column_major || (row_dimension == 1) || (column_dimension == 1)) {
			const auto end = this->cend();
			auto it = this->begin();
			while (it != end) {
				*(it++) = static_cast<value_type>(*(first++));
			}
		} else {
			const auto row_end = this->cend_rows();
			auto row_it = this->begin_rows();
			while (row_end != row_it) {
				const auto end = row_it->end();
				auto it = row_it->begin();
				while (it != end) {
					*(it++) = static_cast<value_type>(*(first++));
				}
				++row_it;
			}
		}
	}
};



//! @relates matrix_interface
//!
//! @brief Returns true if the given matrices are equal, else false.
//!
//! @pre The matrices must have equal value_type, row_dimension, and column_dimension.
template<class Lhs
	,class Rhs
#ifndef MTK_DOXYGEN
	,require<impl_linalg::is_matrix_similar<Lhs, Rhs>::value> = 0
#endif
>
constexpr
bool
operator==(const matrix_interface<Lhs>& lhs, const matrix_interface<Rhs>& rhs)
{
	if constexpr (Lhs::row_dimension == dynamic_dimension) {
		if (lhs.rows() != rhs.rows())
			return false;
	}
	if constexpr (Lhs::column_dimension == dynamic_dimension) {
		if (lhs.columns() != rhs.columns())
			return false;
	}

	const auto [p1, p2] = impl_linalg::optimal_range(lhs, rhs);
	const auto lhs_vec_end = p1.second;
	auto lhs_vec_it = p1.first;
	auto rhs_vec_it = p2.first;
	while (lhs_vec_it != lhs_vec_end) {
		const auto lhs_end = lhs_vec_it->cend();
		auto lhs_it = (lhs_vec_it++)->begin();
		auto rhs_it = (rhs_vec_it++)->begin();
		while (lhs_it != lhs_end) {
			if (*(lhs_it++) != *(rhs_it++))
				return false;
		}
	}
	return true;
}

//! @relates matrix_interface
//!
//! @brief Returns !(lhs == rhs)
//!
//! @sa operator==(const matrix_interface<Lhs>&, const matrix_interface<Rhs>&)
template<class Lhs
	,class Rhs
#ifndef MTK_DOXYGEN
	,require<impl_linalg::is_matrix_similar<Lhs, Rhs>::value> = 0
#endif
>
constexpr
bool
operator!=(const matrix_interface<Lhs>& lhs, const matrix_interface<Rhs>& rhs)
{
	return !(lhs == rhs);
}

//! @relates matrix_interface
//!
//! @brief Returns a copy of the given matrix.
template<class Rhs>
constexpr
auto
operator+(const matrix_interface<Rhs>& rhs)
{
	using mat = typename matrix_traits<Rhs>::template rebind<typename Rhs::value_type, Rhs::row_dimension, Rhs::column_dimension, Rhs::options>;
	return mat(static_cast<const Rhs&>(rhs));
}

//! @relates matrix_interface
//!
//! @brief Returns the additiative inverse of the given matrix.
template<class Rhs>
constexpr
auto
operator-(const matrix_interface<Rhs>& rhs)
{
	using mat = typename matrix_traits<Rhs>::template rebind<typename Rhs::value_type, Rhs::row_dimension, Rhs::column_dimension, Rhs::options>;
	mat ret(static_cast<const Rhs&>(rhs));
	for (auto& el : ret) {
		el = -el;
	}
	return ret;
}

//! @relates matrix_interface
//!
//! @brief Adds the right hand side to the left.
//!
//! Returns a reference to the left hand side.
//!
//! @pre The matrices must have equal value_type, row_dimension, and column_dimension.
//! @pre The matrices must have the same number of rows and the same number of columns.
template<class Lhs
	,class Rhs
#ifndef MTK_DOXYGEN
	,require<impl_linalg::is_matrix_similar<Lhs, Rhs>::value> = 0
	,require<impl_linalg::is_mutable_reference_or_value<Lhs&>::value> = 0
#endif
>
constexpr
Lhs&
operator+=(matrix_interface<Lhs>& lhs, const matrix_interface<Rhs>& rhs)
{
	if constexpr (Lhs::row_dimension == dynamic_dimension)
		MTK_PRECOND_LOW(lhs.rows() == rhs.rows());
	if constexpr (Lhs::column_dimension == dynamic_dimension)
		MTK_PRECOND_LOW(lhs.columns() == rhs.columns());

	const auto [p1, p2] = impl_linalg::optimal_range(lhs, rhs);
	const auto lhs_vec_end = p1.second;
	auto lhs_vec_it = p1.first;
	auto rhs_vec_it = p2.first;
	while (lhs_vec_it != lhs_vec_end) {
		const auto lhs_end = lhs_vec_it->cend();
		auto lhs_it = (lhs_vec_it++)->begin();
		auto rhs_it = (rhs_vec_it++)->begin();
		while (lhs_it != lhs_end) {
			*(lhs_it++) += *(rhs_it++);
		}
	}
	return static_cast<Lhs&>(lhs);
}

#ifndef MTK_DOXYGEN
template<class Lhs
	,class Rhs
	,require<impl_linalg::is_matrix_similar<Lhs, Rhs>::value> = 0
	,require<impl_linalg::is_mutable_reference<Lhs>::value> = 0
>
constexpr
Lhs
operator+=(Lhs lhs, const matrix_interface<Rhs>& rhs)
{
	static_cast<matrix_interface<Lhs>&>(lhs) += rhs;
	return lhs;
}
#endif

//! @relates matrix_interface
//!
//! @brief Returns the sum of the given matrices.
//!
//! @sa operator+=(matrix_interface<Lhs>&, const matrix_interface<Rhs>&)
template<class Lhs
	,class Rhs
#ifndef MTK_DOXYGEN
	,require<impl_linalg::is_matrix_similar<Lhs, Rhs>::value> = 0
#endif
>
constexpr
auto
operator+(const matrix_interface<Lhs>& lhs, const matrix_interface<Rhs>& rhs)
{
	using mat1 = typename matrix_traits<Lhs>::template rebind<typename Lhs::value_type, Lhs::row_dimension, Lhs::column_dimension, Lhs::options | Rhs::options>;
	using mat2 = typename matrix_traits<Rhs>::template rebind<typename Rhs::value_type, Rhs::row_dimension, Rhs::column_dimension, Lhs::options | Rhs::options>;
	using mat_mtk = matrix<typename Lhs::value_type, Lhs::row_dimension, Lhs::column_dimension, Lhs::options | Rhs::options>;
	using ret_mat = std::conditional_t<std::is_same_v<mat1, mat_mtk>, mat2, mat1>;

	ret_mat ret(static_cast<const Lhs&>(lhs));
	ret += rhs;
	return ret;
}

//! @relates matrix_interface
//!
//! @brief Subtracts the right hand side from the left.
//!
//! Returns a reference to the left hand side.
//!
//! @pre The matrices must have equal value_type, row_dimension, and column_dimension.
//! @pre The matrices must have the same number of rows and the same number of columns.
template<class Lhs
	,class Rhs
#ifndef MTK_DOXYGEN
	,require<impl_linalg::is_matrix_similar<Lhs, Rhs>::value> = 0
	,require<impl_linalg::is_mutable_reference_or_value<Lhs&>::value> = 0
#endif
>
constexpr
Lhs&
operator-=(matrix_interface<Lhs>& lhs, const matrix_interface<Rhs>& rhs)
{
	if constexpr (Lhs::row_dimension == dynamic_dimension)
		MTK_PRECOND_LOW(lhs.rows() == rhs.rows());
	if constexpr (Lhs::column_dimension == dynamic_dimension)
		MTK_PRECOND_LOW(lhs.columns() == rhs.columns());

	const auto [p1, p2] = impl_linalg::optimal_range(lhs, rhs);
	const auto lhs_vec_end = p1.second;
	auto lhs_vec_it = p1.first;
	auto rhs_vec_it = p2.first;
	while (lhs_vec_it != lhs_vec_end) {
		const auto lhs_end = lhs_vec_it->cend();
		auto lhs_it = (lhs_vec_it++)->begin();
		auto rhs_it = (rhs_vec_it++)->begin();
		while (lhs_it != lhs_end) {
			*(lhs_it++) -= *(rhs_it++);
		}
	}
	return static_cast<Lhs&>(lhs);
}

#ifndef MTK_DOXYGEN
template<class Lhs
	,class Rhs
	,require<impl_linalg::is_matrix_similar<Lhs, Rhs>::value> = 0
	,require<impl_linalg::is_mutable_reference<Lhs>::value> = 0
>
constexpr
Lhs
operator-=(Lhs lhs, const matrix_interface<Rhs>& rhs)
{
	static_cast<matrix_interface<Lhs>&>(lhs) -= rhs;
	return lhs;
}
#endif

//! @relates matrix_interface
//!
//! @brief Returns the difference of the given matrices.
//!
//! @sa operator-=(matrix_interface<Lhs>&, const matrix_interface<Rhs>&)
template<class Lhs
	,class Rhs
#ifndef MTK_DOXYGEN
	,require<impl_linalg::is_matrix_similar<Lhs, Rhs>::value> = 0
#endif
>
constexpr
auto
operator-(const matrix_interface<Lhs>& lhs, const matrix_interface<Rhs>& rhs)
{
	using mat1 = typename matrix_traits<Lhs>::template rebind<typename Lhs::value_type, Lhs::row_dimension, Lhs::column_dimension, Lhs::options | Rhs::options>;
	using mat2 = typename matrix_traits<Rhs>::template rebind<typename Rhs::value_type, Rhs::row_dimension, Rhs::column_dimension, Lhs::options | Rhs::options>;
	using mat_mtk = matrix<typename Lhs::value_type, Lhs::row_dimension, Lhs::column_dimension, Lhs::options | Rhs::options>;
	using ret_mat = std::conditional_t<std::is_same_v<mat1, mat_mtk>, mat2, mat1>;

	ret_mat ret(static_cast<const Lhs&>(lhs));
	ret -= rhs;
	return ret;
}

//! @relates matrix_interface
//!
//! @brief Multiplies the given matrix by the given scalar.
//!
//! Returns a reference to the matrix.
template<class Lhs
#ifndef MTK_DOXYGEN
	,require<impl_linalg::is_mutable_reference_or_value<Lhs&>::value> = 0
#endif
>
constexpr
Lhs&
operator*=(matrix_interface<Lhs>& lhs, typename Lhs::value_type rhs)
{
	for (auto& el : lhs) {
		el *= rhs;
	}
	return static_cast<Lhs&>(lhs);
}

#ifndef MTK_DOXYGEN
template<class Lhs
	,require<impl_linalg::is_mutable_reference<Lhs>::value> = 0
>
constexpr
Lhs
operator*=(Lhs lhs, typename Lhs::value_type rhs)
{
	static_cast<matrix_interface<Lhs>&>(lhs) *= rhs;
	return lhs;
}
#endif

//! @relates matrix_interface
//!
//! @brief Returns the product of the given matrix and scalar.
template<class Lhs>
constexpr
auto
operator*(const matrix_interface<Lhs>& lhs, typename Lhs::value_type rhs)
{
	using ret_mat = typename matrix_traits<Lhs>::template rebind<typename Lhs::value_type, Lhs::row_dimension, Lhs::column_dimension, Lhs::options>;
	ret_mat ret(lhs);
	ret *= rhs;
	return ret;
}

//! @relates matrix_interface
//!
//! @brief Returns the product of the given matrix and scalar.
template<class Rhs>
constexpr
auto
operator*(typename Rhs::value_type lhs, const matrix_interface<Rhs>& rhs)
{
	using ret_mat = typename matrix_traits<Rhs>::template rebind<typename Rhs::value_type, Rhs::row_dimension, Rhs::column_dimension, Rhs::options>;
	ret_mat ret(rhs);
	ret *= lhs;
	return ret;
}

//! @relates matrix_interface
//!
//! @brief Divides the given matrix by the given scalar.
//!
//! Returns a reference to the matrix.
template<class Lhs
#ifndef MTK_DOXYGEN
	,require<impl_linalg::is_mutable_reference_or_value<Lhs&>::value> = 0
#endif
>
constexpr
Lhs&
operator/=(matrix_interface<Lhs>& lhs, typename Lhs::value_type rhs)
{
	for (auto& el : lhs) {
		el /= rhs;
	}
	return static_cast<Lhs&>(lhs);
}

#ifndef MTK_DOXYGEN
template<class Lhs
	,require<impl_linalg::is_mutable_reference<Lhs>::value> = 0
>
constexpr
Lhs
operator/=(Lhs lhs, typename Lhs::value_type rhs)
{
	static_cast<matrix_interface<Lhs>&>(lhs) /= rhs;
	return lhs;
}
#endif

//! @relates matrix_interface
//!
//! @brief Returns the division of the given matrix by the given scalar.
template<class Lhs>
constexpr
auto
operator/(const matrix_interface<Lhs>& lhs, typename Lhs::value_type rhs)
{
	using ret_mat = typename matrix_traits<Lhs>::template rebind<typename Lhs::value_type, Lhs::row_dimension, Lhs::column_dimension, Lhs::options>;
	ret_mat ret(lhs);
	ret /= rhs;
	return ret;
}

//! @relates matrix_interface
//!
//! @brief Multiplies the the left hand side by the right.
//!
//!	Returns a reference to the left hand side.
//!
//! @pre lhs.row(0).dot(rhs.column(0)) must be well defined.
template<class Lhs
	,class Rhs
	,require<impl_linalg::is_matrix_similar<decltype(std::declval<Lhs&>().row(0)), decltype(std::declval<Rhs&>().column(0))>::value> = 0>
constexpr
Lhs&
operator*=(matrix_interface<Lhs>& lhs, const matrix_square_interface<Rhs>& rhs)
{
	static_cast<Lhs&>(lhs) = lhs * rhs;
	return static_cast<Lhs&>(lhs);
}

//! @relates matrix_interface
//!
//! @brief Returns the product of the given matrices.
//!
//! @pre lhs.row(0).dot(rhs.column(0)) must be well defined.
template<class Lhs
	,class Rhs
	,require<impl_linalg::is_matrix_similar<decltype(std::declval<Lhs&>().row(0)), decltype(std::declval<Rhs&>().column(0))>::value> = 0>
constexpr
auto
operator*(const matrix_interface<Lhs>& lhs, const matrix_interface<Rhs>& rhs)
{
	using mat1 = typename matrix_traits<Lhs>::template rebind<typename Lhs::value_type, Lhs::row_dimension, Rhs::column_dimension, Lhs::options | Rhs::options>;
	using mat2 = typename matrix_traits<Rhs>::template rebind<typename Rhs::value_type, Lhs::row_dimension, Rhs::column_dimension, Lhs::options | Rhs::options>;
	using mat_mtk = matrix<typename Lhs::value_type, Lhs::row_dimension, Rhs::column_dimension, Lhs::options | Rhs::options>;
	using mat = std::conditional_t<std::is_same_v<mat1, mat_mtk>, mat2, mat1>;

	const auto create_mat = [](size_t rows, size_t cols) {
		if constexpr ((mat::row_dimension == dynamic_dimension) && (mat::column_dimension == dynamic_dimension))
			return mat(rows, cols);
		else if constexpr (mat::row_dimension == dynamic_dimension)
			return mat(rows);
		else if constexpr (mat::column_dimension == dynamic_dimension)
			return mat(cols);
		else
			return mat();
	};

	if constexpr (Lhs::row_dimension == dynamic_dimension)
		MTK_PRECOND_LOW(lhs.rows() == rhs.columns());

	mat ret = create_mat(lhs.rows(), rhs.columns());

	const auto row_end = lhs.cend_rows();
	auto row_it = lhs.begin_rows();
	auto dst_row = ret.begin_rows();
	while (row_it != row_end) {
		const auto col_end = rhs.cend_columns();
		auto col_it = rhs.begin_columns();
		auto it = (dst_row++)->begin();
		while (col_it != col_end) {
			*(it++) = row_it->dot(*(col_it++));
		}
		++row_it;
	}
	return ret;
}

//! @}

} // namespace mtk

#ifndef MTK_DOXYGEN
	#ifndef MTK_LINALG_VECTOR_INTERFACE_HPP
		#include <mtk/linalg/vector_interface.hpp>
	#endif
#endif

#endif
