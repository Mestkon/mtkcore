#ifndef MTK_LINALG_MATRIX_IMPL_FWD_HPP
#define MTK_LINALG_MATRIX_IMPL_FWD_HPP

#include <mtk/linalg_fwd.hpp>

#include <utility>

namespace mtk {

template<class Derived>
class matrix_interface;

template<class Derived>
class vector_interface;

template<class Derived>
class matrix_square_interface;


namespace impl_linalg {

template<class Mat1
	,class Mat2
	,class = void>
struct is_matrix_similar_impl :
	std::false_type { };

template<class Mat1
	,class Mat2>
struct is_matrix_similar_impl<Mat1, Mat2
	,std::void_t<void
		,require<std::is_same_v<typename Mat1::value_type, typename Mat2::value_type>>
		,require<Mat1::row_dimension == Mat2::row_dimension>
		,require<Mat1::column_dimension == Mat2::column_dimension>
	>> : std::true_type { };

template<class Vec1
	,class Vec2
	,class = void>
struct is_vector_similar_impl :
	std::false_type { };

template<class Vec1
	,class Vec2>
struct is_vector_similar_impl<Vec1, Vec2
	,std::void_t<void
		,require<(Vec1::row_dimension == 1) || (Vec1::column_dimension == 1)>
		,require<std::is_same_v<typename Vec1::value_type, typename Vec2::value_type>>
		,require<((Vec1::row_dimension == Vec2::row_dimension) && (Vec1::column_dimension == Vec2::column_dimension)) ||
			((Vec1::row_dimension == Vec2::column_dimension) && (Vec1::column_dimension == Vec2::row_dimension))>
	>> : std::true_type { };

template<class Mat1
	,class Mat2>
struct is_matrix_similar :
	std::disjunction<is_matrix_similar_impl<Mat1, Mat2>, is_vector_similar_impl<Mat1, Mat2>>
{ };

template<class Mat
	,class = void>
struct is_reference_impl :
	std::false_type { };

template<class Mat>
struct is_reference_impl<Mat
	,std::void_t<void
		,require<matrix_traits<Mat>::_is_reference>
	>> : std::true_type { };

template<class Mat>
struct is_reference :
	is_reference_impl<std::decay_t<Mat>> { };



template<class Mat
	,class = void>
struct is_mutable_reference_impl :
	std::false_type { };

template<class Mat>
struct is_mutable_reference_impl<Mat
	,std::void_t<void
		,require<matrix_traits<Mat>::_is_reference>
		,require<!matrix_traits<Mat>::_is_const>
	>> : std::true_type { };

template<class Mat>
struct is_mutable_reference :
	is_mutable_reference_impl<std::decay_t<Mat>> { };

template<class Mat
	,class = void>
struct is_mutable_reference_or_value :
	std::false_type { };

template<class Mat>
struct is_mutable_reference_or_value<Mat
	,std::void_t<void
		,require<is_mutable_reference<Mat>::value ||
			(!is_reference<Mat>::value && std::is_reference_v<Mat>)>
	>> : std::true_type { };



template<class Iter>
class step_iterator;

template<class Iter
	,class ConstIter
	,size_t R
	,size_t C
	,matrix_options Opt
	,bool IsConst = std::is_same_v<Iter, ConstIter>>
class matrix_vector_reference;

template<class Iter
	,class ConstIter
	,size_t R
	,size_t C
	,matrix_options Opt
	,bool IsR>
class matrix_vector_iterator;



template<class Mat>
constexpr
auto
optimal_range(Mat& m)
{
	using mat = std::decay_t<Mat>;
	if constexpr (mat::_is_column_major)
		return std::make_pair(m.begin_columns(), m.cend_columns());
	else
		return std::make_pair(m.begin_rows(), m.cend_rows());
}

template<class Mat1
	,class Mat2>
constexpr
auto
optimal_range(Mat1& m1, Mat2& m2)
{
	using mat1 = std::decay_t<Mat1>;
	using mat2 = std::decay_t<Mat2>;
	if constexpr (mat1::_is_column_major && mat2::_is_column_major) {
		const auto p1 = std::make_pair(m1.begin_columns(), m1.cend_columns());
		const auto p2 = std::make_pair(m2.begin_columns(), m2.cend_columns());
		return std::make_pair(p1, p2);
	} else {
		const auto p1 = std::make_pair(m1.begin_rows(), m1.cend_rows());
		const auto p2 = std::make_pair(m2.begin_rows(), m2.cend_rows());
		return std::make_pair(p1, p2);
	}
}


} // namespace impl_linalg
} // namespace mtk

#endif
