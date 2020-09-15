#ifndef MTK_LINALG_MATRIX_CONTAINER_INTERFACE_HPP
#define MTK_LINALG_MATRIX_CONTAINER_INTERFACE_HPP

//! @file
//! Contains the matrix_container_interface definition.

#include <mtk/linalg_fwd.hpp>

#ifndef MTK_DOXYGEN
	#include <../src/mtk/linalg/matrix_impl_fwd.hpp>
#endif

#include <mtk/core/assert.hpp>

#include <iterator>

namespace mtk {

//! @defgroup mat_cont_iface mtk/linalg/matrix_container_interface.hpp
//! @{

//! @brief CRTP class which defines the container interface for matrices.
//!
//! @pre Derived must be the most derived type.
//! @pre mtk::matrix_traits must be specialized for Derived.
template<class Derived>
class matrix_container_interface
{
public:
	using _trait = matrix_traits<Derived>;
	using _ctype = typename _trait::value_type;

	using value_type = std::remove_const_t<_ctype>; //!< STL typedef.
	using size_type = size_t; //!< STL typedef.
	using difference_type = ptrdiff_t; //!< STL typedef.
	using reference = _ctype&; //!< STL typedef.
	using const_reference = const _ctype&; //!< STL typedef.
	using pointer = _ctype*; //!< STL typedef.
	using const_pointer = const _ctype*; //!< STL typedef.
	using iterator = typename _trait::iterator; //!< STL typedef.
	using const_iterator = typename _trait::const_iterator; //!< STL typedef.
	using reverse_iterator = std::reverse_iterator<iterator>; //!< STL typedef.
	using const_reverse_iterator = std::reverse_iterator<const_iterator>; //!< STL typedef.

	//! The compile time number of rows in the matrix.
	static constexpr
	size_type
	row_dimension = _trait::row_dimension;

	//! The compile time number of columns in the matrix.
	static constexpr
	size_type
	column_dimension = _trait::column_dimension;

	//! The compile time options of the matrix.
	static constexpr
	matrix_options
	options = _trait::options;



	//! Returns the number of rows in the matrix.
	constexpr
	size_type
	rows() const
	{
		return _trait::rows(static_cast<const Derived&>(*this));
	}

	//! Returns the number of columns in the matrix.
	constexpr
	size_type
	columns() const
	{
		return _trait::columns(static_cast<const Derived&>(*this));
	}

	//! Returns the number of elements in the matrix.
	constexpr
	size_type
	size() const
	{
		return this->rows()*this->columns();
	}

	//! Returns the number of elements in the matrix.
	constexpr
	size_type
	max_size() const
	{
		//Matrices are not resizable
		return this->size();
	}

	//! Returns true if the size is equal to 0, else false.
	[[nodiscard]]
	constexpr
	bool
	empty() const
	{
		return (this->size() == 0);
	}



	//! @brief Returns an iterator to the beginning of the matrix.
	//! @note The iteration order is dependent on the memory layout of the matrix.
	constexpr
	iterator
	begin()
	{
		return _trait::begin(static_cast<Derived&>(*this));
	}

	//! @copydoc begin()
	constexpr
	const_iterator
	begin() const
	{
		return _trait::begin(static_cast<const Derived&>(*this));
	}

	//! @copydoc begin()
	constexpr
	const_iterator
	cbegin() const
	{
		return this->begin();
	}

	//! @brief Returns an iterator to the end of the matrix.
	//! @note The iteration order is dependent on the memory layout of the matrix.
	constexpr
	iterator
	end()
	{
		return _trait::end(static_cast<Derived&>(*this));
	}

	//! @copydoc end()
	constexpr
	const_iterator
	end() const
	{
		return _trait::end(static_cast<const Derived&>(*this));
	}

	//! @copydoc end()
	constexpr
	const_iterator
	cend() const
	{
		return this->end();
	}

	//! Returns an iterator to the beginning of the reversed range.
	constexpr
	reverse_iterator
	rbegin()
	{
		return reverse_iterator(this->end());
	}

	//! @copydoc rbegin()
	constexpr
	const_reverse_iterator
	rbegin() const
	{
		return const_reverse_iterator(this->end());
	}

	//! @copydoc rbegin()
	constexpr
	const_reverse_iterator
	crbegin() const
	{
		return this->rbegin();
	}

	//! Returns an iterator to the end of the reversed range.
	constexpr
	reverse_iterator
	rend()
	{
		return reverse_iterator(this->begin());
	}

	//! @copydoc rend()
	constexpr
	const_reverse_iterator
	rend() const
	{
		return const_reverse_iterator(this->begin());
	}

	//! @copydoc rend()
	constexpr
	const_reverse_iterator
	crend() const
	{
		return this->rend();
	}

	//! Swaps this matrix instance with the given matrix of same type.
#ifndef MTK_DOXYGEN
	template<bool IsRef = impl_linalg::is_reference<Derived>::value
		,require<IsRef == impl_linalg::is_reference<Derived>::value> = 0
		,require<!IsRef> = 0>
#endif
	constexpr
	void
	swap(Derived& other) noexcept(noexcept(std::swap(other, other)))
	{
		std::swap(static_cast<Derived&>(*this), other);
	}

#ifndef MTK_DOXYGEN
	template<class Other
		,require<impl_linalg::is_matrix_similar<Derived, std::decay_t<Other>>::value> = 0
		,require<impl_linalg::is_mutable_reference_or_value<Other>::value> = 0
		,bool IsVal = impl_linalg::is_mutable_reference_or_value<Derived&>::value
		,require<IsVal == impl_linalg::is_mutable_reference_or_value<Derived&>::value> = 0
		,require<IsVal> = 0
	>
	constexpr
	void
	swap(Other&& other)
	{
		if constexpr (row_dimension == dynamic_dimension)
			MTK_IMPL_LIB_ASSERT(this->rows() == other.rows());
		if constexpr (column_dimension == dynamic_dimension)
			MTK_IMPL_LIB_ASSERT(this->columns() == other.columns());

		using mat = matrix<value_type, row_dimension, column_dimension, options>;
		mat tmp(std::move(static_cast<Derived&>(*this)));
		static_cast<Derived&>(*this) = std::move(other);
		other = std::move(tmp);
	}
#endif
};

//! @relates matrix_container_interface
//!
//! @brief Swaps the given matrices.
template<class Mat1
	,class Mat2
#ifndef MTK_DOXYGEN
	,require<impl_linalg::is_matrix_similar<Mat1, Mat2>::value> = 0
	,require<!impl_linalg::is_reference<Mat1>::value> = 0
	,require<!impl_linalg::is_reference<Mat2>::value> = 0
#endif
>
constexpr
auto
swap(matrix_container_interface<Mat1>& a, matrix_container_interface<Mat2>& b)
#ifndef MTK_DOXYGEN
	MTK_RETURNS(static_cast<Mat1&>(a).swap(static_cast<Mat2&>(b)))
#else
	;
#endif

#ifndef MTK_DOXYGEN
template<class Mat1
	,class Mat2
	,require<impl_linalg::is_matrix_similar<Mat1, Mat2>::value> = 0
	,require<!impl_linalg::is_reference<Mat1>::value> = 0
	,require<impl_linalg::is_mutable_reference<Mat2>::value> = 0>
constexpr
auto
swap(matrix_container_interface<Mat1>& a, Mat2 b)
	MTK_RETURNS(static_cast<Mat1&>(a).swap(b))

template<class Mat1
	,class Mat2
	,require<impl_linalg::is_matrix_similar<Mat1, Mat2>::value> = 0
	,require<impl_linalg::is_mutable_reference<Mat1>::value> = 0
	,require<!impl_linalg::is_reference<Mat2>::value> = 0>
constexpr
auto
swap(Mat1 a, matrix_container_interface<Mat2>& b)
	MTK_RETURNS(a.swap(static_cast<Mat2&>(b)))

template<class Mat1
	,class Mat2
	,require<impl_linalg::is_matrix_similar<Mat1, Mat2>::value> = 0
	,require<impl_linalg::is_mutable_reference<Mat1>::value> = 0
	,require<impl_linalg::is_mutable_reference<Mat2>::value> = 0>
constexpr
auto
swap(Mat1 a, Mat2 b)
	MTK_RETURNS(a.swap(b))
#endif

//! @}

} // namespace mtk

#endif
