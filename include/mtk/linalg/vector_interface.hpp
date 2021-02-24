#ifndef MTK_LINALG_VECTOR_INTERFACE_HPP
#define MTK_LINALG_VECTOR_INTERFACE_HPP

//! @file
//! Contains the vector_interface definition.

#include <mtk/linalg/matrix_interface.hpp>

#include <mtk/core/type_traits.hpp>

#include <cmath>

namespace mtk {
namespace impl_linalg {
template<class Derived>
struct vector_no_base { };
template<class Derived>
struct vector_normalize
{
	void
	normalize()
	{
		auto& self = static_cast<Derived&>(*this);
		MTK_PRECOND_LOW(self.length() != decltype(self.length())());
		self /= self.length();
	}
};
template<class Derived
	,class Base>
struct vector_x :
	public Base
{
	constexpr
	decltype(auto)
	x()
	{
		return static_cast<Derived&>(*this).value(0);
	}

	constexpr
	decltype(auto)
	x() const
	{
		return static_cast<const Derived&>(*this).value(0);
	}
};
template<class Derived
	,class Base>
struct vector_y :
	public Base
{
	constexpr
	decltype(auto)
	y()
	{
		return static_cast<Derived&>(*this).value(1);
	}

	constexpr
	decltype(auto)
	y() const
	{
		return static_cast<const Derived&>(*this).value(1);
	}
};
template<class Derived
	,class Base>
struct vector_z :
	public Base
{
	constexpr
	decltype(auto)
	z()
	{
		return static_cast<Derived&>(*this).value(2);
	}

	constexpr
	decltype(auto)
	z() const
	{
		return static_cast<const Derived&>(*this).value(2);
	}
};
template<class Derived
	,class Base>
struct vector_w :
	public Base
{
	constexpr
	decltype(auto)
	w()
	{
		return static_cast<Derived&>(*this).value(3);
	}

	constexpr
	decltype(auto)
	w() const
	{
		return static_cast<const Derived&>(*this).value(3);
	}
};
template<class Derived>
struct vector_base
{
	static constexpr bool is_mut_or_val = impl_linalg::is_mutable_reference_or_value<Derived&>::value;
	static constexpr bool is_int = std::is_integral_v<std::decay_t<typename matrix_traits<Derived>::value_type>>;
	static constexpr size_t row_dim = matrix_traits<Derived>::row_dimension;
	static constexpr size_t col_dim = matrix_traits<Derived>::column_dimension;
	static constexpr size_t dim = (row_dim == 1 ? col_dim : row_dim);

	using t1 = std::conditional_t<is_mut_or_val && !is_int,
		vector_normalize<Derived>,
		vector_no_base<Derived>>;

	using t2 = std::conditional_t<(dim >= 1) && (dim <= 4),
		vector_x<Derived, t1>,
		t1>;

	using t3 = std::conditional_t<(dim >= 2) && (dim <= 4),
		vector_y<Derived, t2>,
		t2>;

	using t4 = std::conditional_t<(dim >= 3) && (dim <= 4),
		vector_z<Derived, t3>,
		t3>;

	using t5 = std::conditional_t<(dim == 4),
		vector_w<Derived, t4>,
		t4>;

	using type = t5;
};
} // namespace impl_linalg

//! @defgroup vec_iface mtk/linalg/vector_interface.hpp
//! @{

//! @brief CRTP class which defines the basic interface for vectors.
//!
//! Row vectors and column vectors can be used interchangeably where applicable.
//!
//! @pre Derived must be the most derived type.
//! @pre mtk::matrix_traits must be specialized for Derived.
//! @pre The scalar type of Derived must be either a signed integral type,
//! a floating point type, or a std::complex<> type.
//! @pre Either row_dimension or column_dimension must be 1.
template<class Derived>
class vector_interface :
	public matrix_interface<Derived>
#ifndef MTK_DOXYGEN
	,public impl_linalg::vector_base<Derived>::type
#endif
{
public:
	using _base = matrix_interface<Derived>;
	using typename _base::value_type;
	using typename _base::reference;
	using typename _base::const_reference;
	using _base::row_dimension;
	using _base::column_dimension;
	using _base::options;

	//! The compile time dimension of the vector.
	static constexpr
	size_t
	dimension = (row_dimension == 1 ? column_dimension : row_dimension);

	static_assert(row_dimension*column_dimension == dimension);

	static constexpr
	bool
	_is_complex = std::is_same_v<value_type, std::complex<make_real_t<value_type>>>;

	//! Retruns the euclidian length of the vector.
	make_real_t<value_type>
	length() const
	{
		return std::sqrt(this->length_squared());
	}

	//! Returns the square of the euclidian length of the vecotr.
	constexpr
	make_real_t<value_type>
	length_squared() const
	{
		if constexpr (_is_complex) {
			return std::real(this->dot(*this));
		} else {
			return static_cast<make_real_t<value_type>>(this->dot(*this));
		}
	}

	//! Retruns the length of the vector using the manhattan metric.
	make_real_t<value_type>
	length_manhattan() const
	{
		static_assert(!_is_complex, ".length_manhattan() must only be used on a non-complex vector");
		make_real_t<value_type> ret = { };
		for (auto el : *this) {
			ret += std::abs(el);
		}
		return ret;
	}



	//! @brief Returns the dot product of the vectors.
	//!
	//! @pre The vectors must have equal value_types and dimension.
	//! @pre The size of the vectors must be equal.
	template<class Other
#ifndef MTK_DOXYGEN
		,require<impl_linalg::is_matrix_similar<Derived, Other>::value> = 0
#endif
	>
	constexpr
	value_type
	dot(const vector_interface<Other>& other) const
	{
		if constexpr (dimension == dynamic_dimension)
			MTK_PRECOND_LOW(this->size() == other.size());

		value_type ret = { };
		const auto end = this->end();
		auto it = this->begin();
		auto first = other.begin();
		while (it != end) {
			if constexpr (_is_complex) {
				ret += (*(it++))*std::conj(*(first++));
			} else {
				ret += (*(it++))*(*(first++));
			}
		}
		return ret;
	}

	//! @brief Returns the cross product of the vectors.
	//!
	//! @note This function is only available for vectors with a fixed size of 3.
	//!
	//! @pre The vectors must have the same value_type.
	template<class Other
#ifndef MTK_DOXYGEN
		,require<impl_linalg::is_matrix_similar<Derived, Other>::value> = 0
		,bool IsVec = dimension
		,require<IsVec == dimension> = 0
		,require<IsVec == 3> = 0
#endif
	>
	constexpr
	auto
	cross(const vector_interface<Other>& other) const
	{
		const auto& self = static_cast<const Derived&>(*this);
		using ret = typename matrix_traits<Derived>::template rebind<value_type, row_dimension, column_dimension, options>;
		return ret(
			self[1]*other[2] - self[2]*other[1],
			self[2]*other[0] - self[0]*other[2],
			self[0]*other[1] - self[1]*other[0]
		);
	}



	//! Returns a normalized copy of the vector.
	auto
	normalized() const
	{
		using vec = typename matrix_traits<Derived>::template rebind<make_real_t<value_type>, row_dimension, column_dimension, options>;

		auto ret = vec(static_cast<const Derived&>(*this));
		ret.normalize();
		return ret;
	}

#ifdef MTK_DOXYGEN
	//! @brief Normalizes the vector.
	//!
	//! @note This function is not available on integral vectors.
	void
	normalize();



	//! @brief Returns the first element.
	//!
	//! @note This function is only available for vectors with
	//! a fixed size between 1 and 4.
	constexpr
	reference
	x();

	//! @copydoc x()
	constexpr
	const_reference
	x() const;

	//! @brief Returns the second element.
	//!
	//! @note This function is only available for vectors with
	//! a fixed size between 2 and 4.
	constexpr
	reference
	y();

	//! @copydoc y()
	constexpr
	const_reference
	y() const;

	//! @brief Returns the third element.
	//!
	//! @note This function is only available for vectors with
	//! a fixed size between 3 and 4.
	constexpr
	reference
	z();

	//! @copydoc z()
	constexpr
	const_reference
	z() const;

	//! @brief Returns the fourth element.
	//!
	//! @note This function is only available for vectors with
	//! a fixed size of 4.
	constexpr
	reference
	w();

	//! @copydoc w()
	constexpr
	const_reference
	w() const;
#endif
};

//! @}

} // namespace mtk

#ifndef MTK_DOXYGEN
	#include <../src/mtk/linalg/matrix_impl.hpp>
#endif

#endif
