#ifndef MTK_LINALG_MATRIX_VECTOR_ITERATOR_HPP
#define MTK_LINALG_MATRIX_VECTOR_ITERATOR_HPP

#include <../src/mtk/linalg/matrix_step_iterator.hpp>
#include <../src/mtk/linalg/matrix_fixed_vector_reference.hpp>

namespace mtk {
namespace impl_linalg {

template<size_t R
	,size_t C>
struct matrix_vector_iterator_data
{
	constexpr
	matrix_vector_iterator_data(size_t, size_t)
	{ };
};

template<size_t C>
struct matrix_vector_iterator_data<dynamic_dimension, C>
{
	constexpr
	matrix_vector_iterator_data(size_t r, size_t) :
		m_rows(r)
	{ }

protected:
	size_t m_rows;
};

template<size_t R>
struct matrix_vector_iterator_data<R, dynamic_dimension>
{
	constexpr
	matrix_vector_iterator_data(size_t, size_t c) :
		m_cols(c)
	{ }

protected:
	size_t m_cols;
};

template<>
struct matrix_vector_iterator_data<dynamic_dimension, dynamic_dimension>
{
	constexpr
	matrix_vector_iterator_data(size_t r, size_t c) :
		m_rows(r),
		m_cols(c)
	 { }

protected:
	size_t m_rows;
	size_t m_cols;
};



template<class Iter
	,class ConstIter
	,size_t R
	,size_t C
	,matrix_options Opt
	,bool IsR>
class matrix_vector_iterator :
	matrix_vector_iterator_data<R, C>
{
	static constexpr
	bool
	_is_column_major = ((Opt & matrix_options::column_major) == matrix_options::column_major);

	static constexpr
	bool
	_is_vector = (R == 1) || (C == 1);

	using _step_iter = step_iterator<Iter>;
	using _cstep_iter = step_iterator<ConstIter>;

	using _row_ref_type = std::conditional_t<!_is_column_major || _is_vector,
		matrix_vector_reference<Iter, ConstIter, 1, C, Opt>,
		matrix_vector_reference<_step_iter, _cstep_iter, 1, C ,Opt>>;
	using _col_ref_type = std::conditional_t<!_is_column_major && !_is_vector,
		matrix_vector_reference<_step_iter, _cstep_iter, R, 1 ,Opt>,
		matrix_vector_reference<Iter, ConstIter, R, 1, Opt>>;

	using _ref_type = std::conditional_t<IsR, _row_ref_type, _col_ref_type>;

public:
	using value_type = matrix<iter::value<Iter>, IsR ? 1 : R, IsR ? C : 1, Opt>;
	using reference = _ref_type;
	struct pointer {
		reference _value;
		constexpr
		reference*
		operator->()
		{
			return &this->_value;
		}
	};
	using difference_type = iter::difference<Iter>;
	using iterator_category = std::input_iterator_tag;

	constexpr
	matrix_vector_iterator() :
		matrix_vector_iterator_data<R, C>(0, 0),
		m_iter(),
		m_idx(0)
	{ }

	constexpr
	matrix_vector_iterator(Iter iter, size_t rows, size_t cols, size_t idx) :
		matrix_vector_iterator_data<R, C>(rows, cols),
		m_iter(iter),
		m_idx(static_cast<difference_type>(idx))
	{ }

	template<class OtherIter
		,require<std::is_convertible_v<OtherIter, Iter>> = 0>
	constexpr
	matrix_vector_iterator(matrix_vector_iterator<OtherIter, ConstIter, R, C, Opt, IsR> iter) :
		matrix_vector_iterator_data<R, C>(iter._rows(), iter._cols()),
		m_iter(iter.m_iter),
		m_idx(iter.m_idx)
	{ }

	constexpr
	reference
	operator*() const
	{
		if constexpr (IsR)
			return this->_get_row();
		else
			return this->_get_col();
	}

	constexpr
	pointer
	operator->() const
	{
		return pointer{**this};
	}

	friend constexpr
	matrix_vector_iterator&
	operator++(matrix_vector_iterator& rhs)
	{
		++rhs.m_idx;
		return rhs;
	}

	friend constexpr
	matrix_vector_iterator
	operator++(matrix_vector_iterator& lhs, int)
	{
		auto cp = lhs;
		++lhs;
		return cp;
	}

	friend constexpr
	matrix_vector_iterator&
	operator--(matrix_vector_iterator& rhs)
	{
		--rhs.m_idx;
		return rhs;
	}

	friend constexpr
	matrix_vector_iterator
	operator--(matrix_vector_iterator lhs, int)
	{
		auto cp = lhs;
		--lhs;
		return cp;
	}

	friend constexpr
	matrix_vector_iterator&
	operator+=(matrix_vector_iterator& lhs, difference_type rhs)
	{
		lhs.m_idx += rhs;
		return lhs;
	}

	friend constexpr
	matrix_vector_iterator
	operator+(matrix_vector_iterator lhs, difference_type rhs)
	{
		lhs += rhs;
		return lhs;
	}

	friend constexpr
	matrix_vector_iterator
	operator+(difference_type lhs, matrix_vector_iterator rhs)
	{
		rhs += lhs;
		return rhs;
	}

	friend constexpr
	matrix_vector_iterator&
	operator-=(matrix_vector_iterator lhs, difference_type rhs)
	{
		lhs.m_idx -= rhs;
		return lhs;
	}

	friend constexpr
	matrix_vector_iterator
	operator-(matrix_vector_iterator lhs, difference_type rhs)
	{
		lhs -= rhs;
		return lhs;
	}

	friend constexpr
	difference_type
	operator-(matrix_vector_iterator lhs, matrix_vector_iterator rhs)
	{
		return (lhs.m_idx - rhs.m_idx);
	}

	friend constexpr
	bool
	operator==(matrix_vector_iterator lhs, matrix_vector_iterator rhs)
	{
		return (lhs.m_idx == rhs.m_idx);
	}

	friend constexpr
	bool
	operator!=(matrix_vector_iterator lhs, matrix_vector_iterator rhs)
	{
		return (lhs.m_idx != rhs.m_idx);
	}

	friend constexpr
	bool
	operator<(matrix_vector_iterator lhs, matrix_vector_iterator rhs)
	{
		return (lhs.m_idx < rhs.m_idx);
	}

	friend constexpr
	bool
	operator>(matrix_vector_iterator lhs, matrix_vector_iterator rhs)
	{
		return (lhs.m_idx > rhs.m_idx);
	}

	friend constexpr
	bool
	operator<=(matrix_vector_iterator lhs, matrix_vector_iterator rhs)
	{
		return (lhs.m_idx <= rhs.m_idx);
	}

	friend constexpr
	bool
	operator>=(matrix_vector_iterator lhs, matrix_vector_iterator rhs)
	{
		return (lhs.m_idx >= rhs.m_idx);
	}

private:
	constexpr
	auto
	_get_row() const
	{
		MTK_PRECOND_LOW(m_idx < this->_rows());
		if constexpr (!_is_column_major || _is_vector) {
			const auto first = m_iter + m_idx*this->_cols();
			return matrix_vector_reference<Iter, ConstIter, 1, C, Opt>(first, 1, this->_cols());
		} else {
			const auto it = m_iter + m_idx;
			const auto step = this->_rows();
			_step_iter first(it, 0, step);
			return matrix_vector_reference<_step_iter, _cstep_iter, 1, C, Opt>(first, 1, this->_cols());
		}
	}

	constexpr
	auto
	_get_col() const
	{
		MTK_PRECOND_LOW(m_idx < this->_cols());
		if constexpr (!_is_column_major && !_is_vector) {
			const auto it = m_iter + m_idx;
			const auto step = this->_cols();
			_step_iter first(it, 0, step);
			return matrix_vector_reference<_step_iter, _cstep_iter, R, 1, Opt>(first, this->_rows(), 1);
		} else {
			const auto first = m_iter + m_idx*this->_rows();
			return matrix_vector_reference<Iter, ConstIter, R, 1, Opt>(first, this->_rows(), 1);
		}
	}

	constexpr
	size_t
	_rows() const
	{
		if constexpr (R == dynamic_dimension)
			return this->m_rows;
		else
			return R;
	}

	constexpr
	size_t
	_cols() const
	{
		if constexpr (C == dynamic_dimension)
			return this->m_cols;
		else
			return C;
	}

	template<class OtherIter
		,class OtherCIter
		,size_t OtherR
		,size_t OtherC
		,matrix_options OtherOpt
		,bool OtherIsR>
	friend class matrix_vector_iterator;

	Iter m_iter;
	difference_type m_idx;
};

} // namespace impl_linalg
} // namespace mtk

#endif
