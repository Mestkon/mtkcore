#include "matrix_defs.hpp"

template<class Mat>
struct test_copy_assignment
{
	void
	operator()() const
	{
		auto m = create_mat<Mat>();
		Mat cp;
		cp = m;

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

TEST_CASE("linalg/matrix: copy assignment copies the given matrix", "[linalg]")
{
	invoke_for_each_type<test_copy_assignment, DYNAMIC_TYPES>();
}

template<class Mat>
struct test_move_assignment
{
	void
	operator()() const
	{
		auto m = create_mat<Mat>();
		Mat cp = m;
		Mat mv;
		mv = std::move(cp);

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

TEST_CASE("linalg/matrix: move assignment copies the given matrix", "[linalg]")
{
	invoke_for_each_type<test_move_assignment, DYNAMIC_TYPES>();
}

template<class Mat>
struct test_transposed
{
	void
	operator()() const
	{
		auto m = create_mat<Mat>();
		auto tp = m.transposed();

		auto r = m.rows();
		auto c = m.columns();
		REQUIRE(tp.rows() == c);
		REQUIRE(tp.columns() == r);

		for (uint i = 0; i < r; ++i) {
			for (uint j = 0; j < c; ++j) {
				REQUIRE(m[i][j] == tp[j][i]);
			}
		}
	}
};

TEST_CASE("linalg/matrix: transposed returns the transpose of the given matrix", "[linalg]")
{
	invoke_for_each_type<test_transposed, TYPES>();
}
