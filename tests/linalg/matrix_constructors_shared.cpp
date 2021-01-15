#include "matrix_defs.hpp"

template<class Mat>
struct test_default_constructor
{
	void
	operator()() const
	{
		Mat m;

		constexpr auto rows = Mat::row_dimension;
		constexpr auto cols = Mat::column_dimension;
		using T = typename Mat::value_type;

		auto r = m.rows();
		auto c = m.columns();
		if constexpr (rows == dynamic_dimension)
			REQUIRE(r == 0);
		else
			REQUIRE(r == rows);

		if constexpr (cols == dynamic_dimension)
			REQUIRE(c == 0);
		else
			REQUIRE(c == cols);

		size_t count = 0;
		for (auto el : m) {
			REQUIRE(el == T());
			++count;
		}

		REQUIRE(count == m.size());
		REQUIRE(count == r*c);
	}
};

TEST_CASE("linalg/matrix: default constructor initializes to zero", "[linalg]")
{
	invoke_for_each_type<test_default_constructor, TYPES>();
}

template<class Mat>
struct test_direct_constructor
{
	void
	operator()() const
	{
		constexpr auto rows = Mat::row_dimension;
		constexpr auto cols = Mat::column_dimension;
		using T = typename Mat::value_type;

		auto m = create_mat<Mat>();

		auto r = m.rows();
		auto c = m.columns();

		if constexpr (rows == dynamic_dimension)
			REQUIRE(r == 5);
		else
			REQUIRE(r == rows);

		if constexpr (cols == dynamic_dimension)
			REQUIRE(c == 5);
		else
			REQUIRE(c == cols);

		for (uint i = 0; i < r; ++i) {
			for (uint j = 0; j < c; ++j) {
				REQUIRE(m[i][j] == data<T>[i][j]);
				REQUIRE(m.value(i, j) == data<T>[i][j]);
			}
		}

		REQUIRE(m.size() == r*c);
	}
};

TEST_CASE("linalg/matrix: direct constructor initializes to given row order values", "[linalg]")
{
	invoke_for_each_type<test_direct_constructor, TYPES>();
}

template<class Mat>
struct test_iterator_constructor
{
	void
	operator()() const
	{
		constexpr auto rows = Mat::row_dimension;
		constexpr auto cols = Mat::column_dimension;
		using T = typename Mat::value_type;

		auto m = create_mat_with_iter<Mat>();

		auto r = m.rows();
		auto c = m.columns();

		if constexpr (rows == dynamic_dimension)
			REQUIRE(r == 5);
		else
			REQUIRE(r == rows);

		if constexpr (cols == dynamic_dimension)
			REQUIRE(c == 5);
		else
			REQUIRE(c == cols);

		size_t count = 0;
		for (uint i = 0; i < r; ++i) {
			for (uint j = 0; j < c; ++j) {
				REQUIRE(m[i][j] == data<T>[i][j]);
				++count;
			}
		}

		REQUIRE(count == m.size());
		REQUIRE(count == r*c);
	}
};

TEST_CASE("linalg/matrix: iterator constructor initializes to given row order values", "[linalg]")
{
	invoke_for_each_type<test_iterator_constructor, TYPES>();
}
