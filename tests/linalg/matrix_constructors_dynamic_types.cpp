#include "matrix_defs.hpp"

template<class Mat>
struct test_size_constructor
{
	void
	operator()() const
	{
		constexpr auto rows = Mat::row_dimension;
		constexpr auto cols = Mat::column_dimension;
		using T = typename Mat::value_type;

		auto m = []() {
			if constexpr ((rows == dynamic_dimension) && (cols == dynamic_dimension))
				return Mat(5, 5);
			else
				return Mat(5);
		}();

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
		for (auto el : m) {
			REQUIRE(el == T());
			++count;
		}

		REQUIRE(count == m.size());
		REQUIRE(count == r*c);
	}
};

TEST_CASE("linalg/matrix: size constructor initializes correct size with elements initialized to zero", "[linalg]")
{
	invoke_for_each_type<test_size_constructor, DYNAMIC_TYPES>();
}

template<class Mat>
struct test_copy_constructor
{
	void
	operator()() const
	{
		auto m = create_mat<Mat>();
		auto cp = m;

		auto r = m.rows();
		auto c = m.columns();
		REQUIRE(cp.rows() == r);
		REQUIRE(cp.columns() == c);

		for (uint i = 0; i < r; ++i) {
			for (uint j = 0; j < c; ++j) {
				REQUIRE(cp[i][j] == m[i][j]);
			}
		}
	}
};

TEST_CASE("linalg/matrix: copy constructor copies the given matrix", "[linalg]")
{
	invoke_for_each_type<test_copy_constructor, DYNAMIC_TYPES>();
}

template<class Mat>
struct test_move_constructor
{
	void
	operator()() const
	{
		auto m = create_mat<Mat>();
		auto cp = m;
		auto mv = std::move(cp);

		auto r = m.rows();
		auto c = m.columns();
		REQUIRE(mv.rows() == r);
		REQUIRE(mv.columns() == c);

		for (uint i = 0; i < r; ++i) {
			for (uint j = 0; j < c; ++j) {
				REQUIRE(mv[i][j] == m[i][j]);
			}
		}
	}
};

TEST_CASE("linalg/matrix: move constructor moves the given matrix", "[linalg]")
{
	invoke_for_each_type<test_move_constructor, DYNAMIC_TYPES>();
}
