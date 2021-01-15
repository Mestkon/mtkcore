#ifndef MTK_TESTS_LINALG_MATRIX_DEFS_HPP
#define MTK_TESTS_LINALG_MATRIX_DEFS_HPP

#include <catch.hpp>

#include <mtk/linalg/matrix.hpp>

using namespace mtk;

#include <mtk/core/preprocessor.hpp>

#pragma GCC diagnostic ignored "-Wfloat-equal"

template<std::size_t S, class T>
using vec = vector<T, S>;

using mat2f = matrix<float, 2, 2>;
using mat3f = matrix<float, 3, 3>;
using mat4f = matrix<float, 4, 4>;
using mat5f = matrix<float, 5, 5>;
using matxf = matrix<float, dynamic_dimension, dynamic_dimension>;

using mat2x3f = matrix<float, 2, 3>;
using mat3x2f = matrix<float, 3, 2>;
using mat3xxf = matrix<float, 3, dynamic_dimension>;
using matxx3f = matrix<float, dynamic_dimension, 3>;

using mat2d = matrix<double, 2, 2>;
using mat3d = matrix<double, 3, 3>;
using mat4d = matrix<double, 4, 4>;
using mat5d = matrix<double, 5, 5>;
using mat6d = matrix<double, 6, 6>;
using matxd = matrix<double, dynamic_dimension, dynamic_dimension>;

using mat2x3d = matrix<double, 2, 3>;
using mat3x2d = matrix<double, 3, 2>;
using mat3xxd = matrix<double, 3, dynamic_dimension>;
using matxx3d = matrix<double, dynamic_dimension, 3>;

using mat2i = matrix<int, 2, 2>;
using mat3i = matrix<int, 3, 3>;
using mat4i = matrix<int, 4, 4>;
using mat5i = matrix<int, 5, 5>;
using mat6i = matrix<int, 6, 6>;
using matxi = matrix<int, dynamic_dimension, dynamic_dimension>;

using mat2x3i = matrix<int, 2, 3>;
using mat3x2i = matrix<int, 3, 2>;
using mat3xxi = matrix<int, 3, dynamic_dimension>;
using matxx3i = matrix<int, dynamic_dimension, 3>;

using mat2cf = matrix<std::complex<float>, 2, 2>;
using mat3cf = matrix<std::complex<float>, 3, 3>;
using mat4cf = matrix<std::complex<float>, 4, 4>;
using mat5cf = matrix<std::complex<float>, 5, 5>;
using matxcf = matrix<std::complex<float>, dynamic_dimension, dynamic_dimension>;

using mat2x3cf = matrix<std::complex<float>, 2, 3>;
using mat3x2cf = matrix<std::complex<float>, 3, 2>;
using mat3xxcf = matrix<std::complex<float>, 3, dynamic_dimension>;
using matxx3cf = matrix<std::complex<float>, dynamic_dimension, 3>;

using cmat2f = matrix<float, 2, 2, matrix_options::column_major>;
using cmat3f = matrix<float, 3, 3, matrix_options::column_major>;
using cmat4f = matrix<float, 4, 4, matrix_options::column_major>;
using cmat5f = matrix<float, 5, 5, matrix_options::column_major>;
using cmatxf = matrix<float, dynamic_dimension, dynamic_dimension, matrix_options::column_major>;

using cmat2x3f = matrix<float, 2, 3, matrix_options::column_major>;
using cmat3x2f = matrix<float, 3, 2, matrix_options::column_major>;
using cmat3xxf = matrix<float, 3, dynamic_dimension, matrix_options::column_major>;
using cmatxx3f = matrix<float, dynamic_dimension, 3, matrix_options::column_major>;

using cmat2d = matrix<double, 2, 2, matrix_options::column_major>;
using cmat3d = matrix<double, 3, 3, matrix_options::column_major>;
using cmat4d = matrix<double, 4, 4, matrix_options::column_major>;
using cmat5d = matrix<double, 5, 5, matrix_options::column_major>;
using cmat6d = matrix<double, 6, 6, matrix_options::column_major>;
using cmatxd = matrix<double, dynamic_dimension, dynamic_dimension, matrix_options::column_major>;

using cmat2x3d = matrix<double, 2, 3, matrix_options::column_major>;
using cmat3x2d = matrix<double, 3, 2, matrix_options::column_major>;
using cmat3xxd = matrix<double, 3, dynamic_dimension, matrix_options::column_major>;
using cmatxx3d = matrix<double, dynamic_dimension, 3, matrix_options::column_major>;

using cmat2i = matrix<int, 2, 2, matrix_options::column_major>;
using cmat3i = matrix<int, 3, 3, matrix_options::column_major>;
using cmat4i = matrix<int, 4, 4, matrix_options::column_major>;
using cmat5i = matrix<int, 5, 5, matrix_options::column_major>;
using cmat6i = matrix<int, 6, 6, matrix_options::column_major>;
using cmatxi = matrix<int, dynamic_dimension, dynamic_dimension, matrix_options::column_major>;

using cmat2x3i = matrix<int, 2, 3, matrix_options::column_major>;
using cmat3x2i = matrix<int, 3, 2, matrix_options::column_major>;
using cmat3xxi = matrix<int, 3, dynamic_dimension, matrix_options::column_major>;
using cmatxx3i = matrix<int, dynamic_dimension, 3, matrix_options::column_major>;

using cmat2cf = matrix<std::complex<float>, 2, 2, matrix_options::column_major>;
using cmat3cf = matrix<std::complex<float>, 3, 3, matrix_options::column_major>;
using cmat4cf = matrix<std::complex<float>, 4, 4, matrix_options::column_major>;
using cmat5cf = matrix<std::complex<float>, 5, 5, matrix_options::column_major>;
using cmatxcf = matrix<std::complex<float>, dynamic_dimension, dynamic_dimension, matrix_options::column_major>;

using cmat2x3cf = matrix<std::complex<float>, 2, 3, matrix_options::column_major>;
using cmat3x2cf = matrix<std::complex<float>, 3, 2, matrix_options::column_major>;
using cmat3xxcf = matrix<std::complex<float>, 3, dynamic_dimension, matrix_options::column_major>;
using cmatxx3cf = matrix<std::complex<float>, dynamic_dimension, 3, matrix_options::column_major>;

#define BASE_TYPE(PRE, SIZE, TYPE) MTK_CONCAT(PRE, MTK_CONCAT(MTK_CONCAT(mat, SIZE), TYPE))
#define SIZE_TYPES(PRE, TYPE) \
	BASE_TYPE(PRE, 2, TYPE), \
	BASE_TYPE(PRE, 3, TYPE), \
	BASE_TYPE(PRE, 4, TYPE), \
	BASE_TYPE(PRE, 5, TYPE), \
	BASE_TYPE(PRE, x, TYPE), \
	BASE_TYPE(PRE, 2x3, TYPE), \
	BASE_TYPE(PRE, 3x2, TYPE), \
	BASE_TYPE(PRE, 3xx, TYPE), \
	BASE_TYPE(PRE, xx3, TYPE)

#define DYNAMIC_SIZE_TYPES(PRE, TYPE) \
	BASE_TYPE(PRE, x, TYPE), \
	BASE_TYPE(PRE, 3xx, TYPE), \
	BASE_TYPE(PRE, xx3, TYPE)

#define ROW_TYPES(MACRO) \
	MACRO(, f), \
	MACRO(, d), \
	MACRO(, i), \
	MACRO(, cf)

#define COL_TYPES(MACRO) \
	MACRO(c, f), \
	MACRO(c, d), \
	MACRO(c, i), \
	MACRO(c, cf)

#define TYPES ROW_TYPES(SIZE_TYPES), COL_TYPES(SIZE_TYPES)
#define DYNAMIC_TYPES ROW_TYPES(DYNAMIC_SIZE_TYPES), COL_TYPES(DYNAMIC_SIZE_TYPES)

template<template<class> class Obj
	,class... Types>
void
invoke_for_each_type()
{
	auto ilist = {(Obj<Types>()(), 1)...};
	MTK_IGNORE(ilist);
};

template<class T>
inline constexpr
T
data[5][5] = { {1, -2, 9, -10, 25}, {-4, 3, -8, 11, -24}, {5, -6, 7, -12, 23}, {-16, 15, -14, 13, -22}, {17, -18, 19, -20, 21} };

template<class Mat
	,size_t R
	,size_t C
	,size_t ...Is>
Mat
create_mat(std::index_sequence<Is...>)
{
	constexpr auto rows = Mat::row_dimension;
	constexpr auto cols = Mat::column_dimension;
	constexpr bool both_dynamic = (rows == dynamic_dimension) && (cols == dynamic_dimension);
	constexpr bool none_dynamic = (rows != dynamic_dimension) && (cols != dynamic_dimension);
	using T = typename Mat::value_type;

	if constexpr (none_dynamic)
		return Mat(data<T>[Is / C][Is % C]...);
	else if constexpr (!both_dynamic)
		return Mat({data<T>[Is / C][Is % C]...});
	else
		return Mat(R, C, {data<T>[Is / C][Is % C]...});
}

template<class Mat>
Mat
create_mat()
{
	constexpr auto rows = Mat::row_dimension;
	constexpr auto cols = Mat::column_dimension;
	constexpr bool both_dynamic = (rows == dynamic_dimension) && (cols == dynamic_dimension);
	constexpr bool none_dynamic = (rows != dynamic_dimension) && (cols != dynamic_dimension);

	if constexpr (none_dynamic)
		return create_mat<Mat, rows, cols>(std::make_index_sequence<rows*cols>());
	else if constexpr (both_dynamic)
		return create_mat<Mat, 5, 5>(std::make_index_sequence<25>());
	else if constexpr (cols == dynamic_dimension)
		return create_mat<Mat, rows, 5>(std::make_index_sequence<rows*5>());
	else
		return create_mat<Mat, 5, cols>(std::make_index_sequence<5*cols>());
}

template<class Mat
	,size_t R
	,size_t C
	,size_t ...Is>
Mat
create_mat_with_iter(std::index_sequence<Is...>)
{
	constexpr auto rows = Mat::row_dimension;
	constexpr auto cols = Mat::column_dimension;
	constexpr bool both_dynamic = (rows == dynamic_dimension) && (cols == dynamic_dimension);
	using T = typename Mat::value_type;

	auto ilist = {data<T>[Is / C][Is % C]...};
	if constexpr (!both_dynamic)
		return Mat(ilist.begin(), ilist.end());
	else
		return Mat(R, C, ilist.begin(), ilist.end());
}

template<class Mat>
Mat
create_mat_with_iter()
{
	constexpr auto rows = Mat::row_dimension;
	constexpr auto cols = Mat::column_dimension;
	constexpr bool both_dynamic = (rows == dynamic_dimension) && (cols == dynamic_dimension);
	constexpr bool none_dynamic = (rows != dynamic_dimension) && (cols != dynamic_dimension);

	if constexpr (none_dynamic)
		return create_mat_with_iter<Mat, rows, cols>(std::make_index_sequence<rows*cols>());
	else if constexpr (both_dynamic)
		return create_mat_with_iter<Mat, 5, 5>(std::make_index_sequence<25>());
	else if constexpr (cols == dynamic_dimension)
		return create_mat_with_iter<Mat, rows, 5>(std::make_index_sequence<rows*5>());
	else
		return create_mat_with_iter<Mat, 5, cols>(std::make_index_sequence<5*cols>());
}

#endif
