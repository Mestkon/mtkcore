#ifndef MTK_LINALG_STEP_ITERATOR_HPP
#define MTK_LINALG_STEP_ITERATOR_HPP

#include <mtk/core/iterator_traits.hpp>

namespace mtk {
namespace impl_linalg {

template<class Iter>
class step_iterator
{
public:
	static_assert(mtk::is_random_access_iterator_v<Iter>);

	using value_type = iter::value<Iter>;
	using difference_type = iter::difference<Iter>;
	using pointer = iter::pointer<Iter>;
	using reference = iter::reference<Iter>;
	using iterator_category = iter::category<Iter>;

	constexpr
	step_iterator() noexcept(std::is_nothrow_default_constructible_v<Iter>) :
		m_iter(),
		m_idx(0),
		m_step(1)
	{ }

	constexpr
	step_iterator(Iter iter, difference_type idx, difference_type step) noexcept(std::is_nothrow_copy_constructible_v<Iter>) :
		m_iter(iter),
		m_idx(idx),
		m_step(step)
	{ }

	template<class OtherIter
		,require<std::is_convertible_v<OtherIter, Iter>> = 0>
	constexpr
	step_iterator(step_iterator<OtherIter> iter) noexcept(std::is_nothrow_constructible_v<Iter, OtherIter>) :
		m_iter(iter.m_iter),
		m_idx(iter.m_idx),
		m_step(iter.m_step)
	{ }

	constexpr
	reference
	operator*() const
	{
		return *(m_iter + m_idx*m_step);
	}

	constexpr
	pointer
	operator->() const
	{
		return &(**this);
	}

	friend constexpr
	step_iterator&
	operator++(step_iterator& rhs)
	{
		++rhs.m_idx;
		return rhs;
	}

	friend constexpr
	step_iterator
	operator++(step_iterator& lhs, int)
	{
		auto cp = lhs;
		++lhs;
		return cp;
	}

	friend constexpr
	step_iterator&
	operator--(step_iterator& rhs)
	{
		--rhs.m_idx;
		return rhs;
	}

	friend constexpr
	step_iterator
	operator--(step_iterator lhs, int)
	{
		auto cp = lhs;
		--lhs;
		return cp;
	}

	friend constexpr
	step_iterator&
	operator+=(step_iterator& lhs, difference_type rhs)
	{
		lhs.m_idx += rhs;
		return lhs;
	}

	friend constexpr
	step_iterator
	operator+(step_iterator lhs, difference_type rhs)
	{
		lhs += rhs;
		return lhs;
	}

	friend constexpr
	step_iterator
	operator+(difference_type lhs, step_iterator rhs)
	{
		rhs += lhs;
		return lhs;
	}

	friend constexpr
	step_iterator&
	operator-=(step_iterator lhs, difference_type rhs)
	{
		lhs.m_idx -= rhs;
		return lhs;
	}

	friend constexpr
	step_iterator
	operator-(step_iterator lhs, difference_type rhs)
	{
		lhs -= rhs;
		return lhs;
	}

	friend constexpr
	difference_type
	operator-(step_iterator lhs, step_iterator rhs)
	{
		return (lhs.m_idx - rhs.m_idx);
	}

	friend constexpr
	bool
	operator==(step_iterator lhs, step_iterator rhs)
	{
		return (lhs.m_idx == rhs.m_idx);
	}

	friend constexpr
	bool
	operator!=(step_iterator lhs, step_iterator rhs)
	{
		return (lhs.m_idx != rhs.m_idx);
	}

	friend constexpr
	bool
	operator<(step_iterator lhs, step_iterator rhs)
	{
		return (lhs.m_idx < rhs.m_idx);
	}

	friend constexpr
	bool
	operator>(step_iterator lhs, step_iterator rhs)
	{
		return (lhs.m_idx > rhs.m_idx);
	}

	friend constexpr
	bool
	operator<=(step_iterator lhs, step_iterator rhs)
	{
		return (lhs.m_idx <= rhs.m_idx);
	}

	friend constexpr
	bool
	operator>=(step_iterator lhs, step_iterator rhs)
	{
		return (lhs.m_idx >= rhs.m_idx);
	}

private:
	template<class OtherIter>
	friend class step_iterator;

	Iter m_iter;
	difference_type m_idx;
	difference_type m_step;
};

} // namespace impl_linalg
} // namespace mtk

#endif
