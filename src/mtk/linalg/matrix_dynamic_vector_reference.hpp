#ifndef MTK_LINALG_MATRIX_DYNAMIC_VECTOR_REFERENCE_HPP
#define MTK_LINALG_MATRIX_DYNAMIC_VECTOR_REFERENCE_HPP

#include <../src/mtk/linalg/matrix_impl_fwd.hpp>

#include <mtk/core/assert.hpp>
#include <mtk/core/iterator_traits.hpp>

namespace mtk {

template<class Iter
	,class ConstIter
	,size_t C
	,matrix_options Opt
	,bool IsConst>
struct matrix_traits<impl_linalg::matrix_vector_reference<Iter, ConstIter, dynamic_dimension, C, Opt, IsConst>>
{
	using _mat = impl_linalg::matrix_vector_reference<Iter, ConstIter, dynamic_dimension, C, Opt, IsConst>;
	static constexpr
	bool
	_is_reference = true;
	static constexpr
	bool
	_is_const = std::is_same_v<Iter, ConstIter>;

	using value_type = std::conditional_t<_is_const,
		const iter::value<Iter>,
		iter::value<Iter>>;
	using iterator = Iter;
	using const_iterator = ConstIter;

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
	column_dimension = C;

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
		return C;
	}

	static constexpr
	iterator
	begin(_mat& m)
	{
		return m.m_iter;
	}

	static constexpr
	const_iterator
	begin(const _mat& m)
	{
		return m.m_iter;
	}

	static constexpr
	iterator
	end(_mat& m)
	{
		return m.m_iter + m.m_rows*C;
	}

	static constexpr
	const_iterator
	end(const _mat& m)
	{
		return m.m_iter + m.m_rows*C;
	}
};



template<class Iter
	,class ConstIter
	,size_t R
	,matrix_options Opt
	,bool IsConst>
struct matrix_traits<impl_linalg::matrix_vector_reference<Iter, ConstIter, R, dynamic_dimension, Opt, IsConst>>
{
	using _mat = impl_linalg::matrix_vector_reference<Iter, ConstIter, R, dynamic_dimension, Opt, IsConst>;
	static constexpr
	bool
	_is_reference = true;
	static constexpr
	bool
	_is_const = std::is_same_v<Iter, ConstIter>;

	using value_type = std::conditional_t<_is_const,
		const iter::value<Iter>,
		iter::value<Iter>>;
	using iterator = Iter;
	using const_iterator = ConstIter;

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
	column_dimension = dynamic_dimension;

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
	columns(const _mat& m)
	{
		return m.m_cols;
	}

	static constexpr
	iterator
	begin(_mat& m)
	{
		return m.m_iter;
	}

	static constexpr
	const_iterator
	begin(const _mat& m)
	{
		return m.m_iter;
	}

	static constexpr
	iterator
	end(_mat& m)
	{
		return m.m_iter + R*m.m_cols;
	}

	static constexpr
	const_iterator
	end(const _mat& m)
	{
		return m.m_iter + R*m.m_cols;
	}
};



namespace impl_linalg {

template<class Iter
	,class ConstIter
	,matrix_options Opt
	,size_t C
	,bool IsConst>
class matrix_vector_reference<Iter, ConstIter, dynamic_dimension, C, Opt, IsConst> :
	public vector_interface<matrix_vector_reference<Iter, ConstIter, dynamic_dimension, C, Opt, IsConst>>
{
public:
	constexpr
	matrix_vector_reference(Iter iter, size_t rows, size_t) :
		m_iter(iter),
		m_rows(rows)
	{ }

	constexpr
	matrix_vector_reference&
	operator=(const matrix_vector_reference& rhs)
	{
		return *this = static_cast<const matrix_interface<matrix_vector_reference>&>(rhs);
	}

	template<class Other
		,require<is_matrix_similar<matrix_vector_reference, Other>::value> = 0>
	constexpr
	matrix_vector_reference&
	operator=(const matrix_interface<Other>& rhs)
	{
		MTK_PRECOND_LOW(this->size() == rhs.size());
		const auto end = this->cend();
		auto it = this->begin();
		auto first = rhs.begin();
		while (it != end) {
			*(it++) = *(first++);
		}
		return *this;
	}

private:
	friend matrix_traits<matrix_vector_reference>;

	Iter m_iter;
	size_t m_rows;
};

template<class Iter
	,class ConstIter
	,size_t C
	,matrix_options Opt>
class matrix_vector_reference<Iter, ConstIter, dynamic_dimension, C, Opt, true> :
	public vector_interface<matrix_vector_reference<Iter, ConstIter, dynamic_dimension, C, Opt, true>>
{
public:
	constexpr
	matrix_vector_reference(Iter iter, size_t rows, size_t) :
		m_iter(iter),
		m_rows(rows)
	{ }

	void operator=(const matrix_vector_reference&) = delete;

private:
	friend matrix_traits<matrix_vector_reference>;

	Iter m_iter;
	size_t m_rows;
};



template<class Iter
	,class ConstIter
	,matrix_options Opt
	,size_t R
	,bool IsConst>
class matrix_vector_reference<Iter, ConstIter, R, dynamic_dimension, Opt, IsConst> :
	public vector_interface<matrix_vector_reference<Iter, ConstIter, R, dynamic_dimension, Opt, IsConst>>
{
public:
	constexpr
	matrix_vector_reference(Iter iter, size_t, size_t cols) :
		m_iter(iter),
		m_cols(cols)
	{ }

	constexpr
	matrix_vector_reference&
	operator=(const matrix_vector_reference& rhs)
	{
		return *this = static_cast<const matrix_interface<matrix_vector_reference>&>(rhs);
	}

	template<class Other
		,require<is_matrix_similar<matrix_vector_reference, Other>::value> = 0>
	constexpr
	matrix_vector_reference&
	operator=(const matrix_interface<Other>& rhs)
	{
		MTK_PRECOND_LOW(this->size() == rhs.size());
		const auto end = this->cend();
		auto it = this->begin();
		auto first = rhs.begin();
		while (it != end) {
			*(it++) = *(first++);
		}
		return *this;
	}

private:
	friend matrix_traits<matrix_vector_reference>;

	Iter m_iter;
	size_t m_cols;
};

template<class Iter
	,class ConstIter
	,size_t R
	,matrix_options Opt>
class matrix_vector_reference<Iter, ConstIter, R, dynamic_dimension, Opt, true> :
	public vector_interface<matrix_vector_reference<Iter, ConstIter, R, dynamic_dimension, Opt, true>>
{
public:
	constexpr
	matrix_vector_reference(Iter iter, size_t, size_t cols) :
		m_iter(iter),
		m_cols(cols)
	{ }

	void operator=(const matrix_vector_reference&) = delete;

private:
	friend matrix_traits<matrix_vector_reference>;

	Iter m_iter;
	size_t m_cols;
};


} // namespace impl_linalg
} // namespace mtk

#endif
