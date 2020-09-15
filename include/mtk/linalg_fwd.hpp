#ifndef MTK_LINALG_FWD_HPP
#define MTK_LINALG_FWD_HPP

//! @file
//! Contains forward declared linalg types.

#include <mtk/core/flag_operators.hpp>
#include <mtk/core/types.hpp>

#include <limits>

namespace mtk {

//! @defgroup linalg_fwd mtk/linalg_fwd.hpp
//! @{

//! @brief Contains the matrix defining traits for
//! a given matrix type T.
//!
//! Specialize this and inherit from the desired interface/base
//! to define a custom matrix type.
template<class T>
struct matrix_traits
#ifdef MTK_DOXYGEN
{
	//! The scalar type of the matrix.
	using value_type = void;
	//! The element-wise iterator of the matrix. Same order as defined in options.
	using iterator = void;
	//! @copydoc iterator
	using const_iterator = void;
	//! @brief Template defining a type for temporary storage.
	//!
	//! This is also the type returned for functions returning a copy like
	//! e.g. transposed() and operator+().
	//!
	//! @pre The type must inherit matrix_interface.
	//! @pre The type must support the constructors of
	//! the corresponding mtk::matrix type.
	template<class Sca
		,size_t Ro
		,size_t Co
		,matrix_options Options>
	using rebind = matrix<Sca, Ro, Co, Options>;
	//! The compile time number of rows in the matrix.
	static constexpr size_t row_dimension = 0;
	//! The compile time number of columns in the matrix.
	static constexpr size_t column_dimension = 0;
	//! The compile time options of the matrix.
	static constexpr matrix_options options = { };
	//! Returns the number of rows in the matrix.
	static constexpr size_t rows(const T&) { return 0; }
	//! Returns the number of columns in the matrix.
	static constexpr size_t columns(const T&) { return 0; }
	//! Returns an iterator to the beginning of the matrix.
	static constexpr iterator begin(T&) { }
	//! @copydoc begin(T&)
	static constexpr const_iterator begin(const T&) { }
	//! Returns an iterator to the end of the matrix.
	static constexpr iterator end(T&) { }
	//! @copydoc end(T&)
	static constexpr const_iterator end(const T&) { }
}
#endif
;



//! Constant representing a dynamic dimension in a matrix.
inline constexpr
size_t
dynamic_dimension = std::numeric_limits<size_t>::max();

//! Option flags for matrices.
enum class matrix_options
{
	//! @brief The memory layout in the matrix will be laid out in a row-major order.
	//!
	//! Mutually exclusive with column_major
	row_major = 0,
	//! @brief The memory layout in the matrix will be laid out in a column-major order.
	//!
	//! Mutually exclusive with row_major
	column_major = (1 << 0)
};
MTK_DEFINE_FLAG_OPERATORS(matrix_options)



template<class Scalar
	,size_t Rows
	,size_t Columns
	,matrix_options Options = matrix_options::row_major>
class matrix;

using matrix2 = matrix<real, 2, 2>; //!< 2 by 2 matrix.
using matrix3 = matrix<real, 3, 3>; //!< 3 by 3 matrix.
using matrix4 = matrix<real, 4, 4>; //!< 4 by 4 matrix.
using matrixx = matrix<real, dynamic_dimension, dynamic_dimension>; //!< x by y matrix.

//! Standard column vector type.
template<class Scalar
	,size_t Dimension>
using vector = matrix<Scalar, Dimension, 1>;

using vector2 = vector<real, 2>; //!< 2 by 1 vector.
using vector3 = vector<real, 3>; //!< 3 by 1 vector.
using vector4 = vector<real, 4>; //!< 4 by 1 vector.
using vectorx = vector<real, dynamic_dimension>; //!< x by 1 vector.

//! Standard row vector type.
template<class Scalar
	,size_t Dimension>
using row_vector = matrix<Scalar, 1, Dimension>;

using row_vector2 = row_vector<real, 2>; //!< 1 by 2 vector.
using row_vector3 = row_vector<real, 3>; //!< 1 by 3 vector.
using row_vector4 = row_vector<real, 4>; //!< 1 by 4 vector.
using row_vectorx = row_vector<real, dynamic_dimension>; //!< 1 by x vector.

//! @}

} // namespace mtk

#endif
