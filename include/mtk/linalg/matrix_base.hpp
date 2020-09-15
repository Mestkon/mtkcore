#ifndef MTK_LINALG_MATRIX_BASE_HPP
#define MTK_LINALG_MATRIX_BASE_HPP

//! @file
//! Contains the matrix_base definition.

#include <mtk/linalg/vector_interface.hpp>
#include <mtk/linalg/matrix_square_interface.hpp>

namespace mtk {

//! @defgroup mat_base mtk/linalg/matrix_base.hpp
//! @{

//! @brief Selects the correct base interface for a given Derived class.
//!
//! Selects:
//!	- vector_interface if either row_dimension or column_dimension is 1
//! - else matrix_square_interface if row_dimension is equal to column_dimension
//! - else matrix_interface
//!
//! @pre Derived must be the most derived type.
//! @pre mtk::matrix_traits must be specialized for Derived.
//! @pre The scalar type of Derived must be either a signed integral type,
//! a floating point type, or a std::complex<> type.
template<class Derived>
using matrix_base =
#ifndef MTK_DOXYGEN
	std::conditional_t<
		(matrix_traits<Derived>::row_dimension == 1) || (matrix_traits<Derived>::column_dimension == 1),
		vector_interface<Derived>,
		std::conditional_t<
			matrix_traits<Derived>::row_dimension == matrix_traits<Derived>::column_dimension,
			matrix_square_interface<Derived>,
			matrix_interface<Derived>>>
#endif
	;

//! @}

} // namespace mtk

#endif
