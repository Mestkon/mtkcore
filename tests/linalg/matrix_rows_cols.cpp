#include "matrix_defs.hpp"

template<class Mat>
struct test_row_iterator
{
	void
	operator()() const
	{
		auto m = create_mat<Mat>();

		auto r = m.rows();
		auto c = m.columns();
		auto row = m.begin_rows();
		for (uint i = 0; i < r; ++i) {
			auto it = row->begin();
			for (uint j = 0; j < c; ++j) {
				REQUIRE(*it == m[i][j]);
				*(it++) = typename Mat::value_type();
				REQUIRE(m[i][j] == typename Mat::value_type());
			}
			REQUIRE(it == row->end());
			++row;
		}
		REQUIRE(row == m.end_rows());
	}
};

TEST_CASE("linalg/matrix: row iterator iterates over the rows of the given matrix", "[linalg]")
{
	invoke_for_each_type<test_row_iterator, TYPES>();
}

template<class Mat>
struct test_column_iterator
{
	void
	operator()() const
	{
		auto m = create_mat<Mat>();

		auto r = m.rows();
		auto c = m.columns();
		auto col = m.begin_columns();
		for (uint j = 0; j < c; ++j) {
			auto it = col->begin();
			for (uint i = 0; i < r; ++i) {
				REQUIRE(*it == m[i][j]);
				*(it++) = typename Mat::value_type();
				REQUIRE(m[i][j] == typename Mat::value_type());
			}
			REQUIRE(it == col->end());
			++col;
		}
		REQUIRE(col == m.end_columns());
	}
};

TEST_CASE("linalg/matrix: column iterator iterates over the columns of the given matrix", "[linalg]")
{
	invoke_for_each_type<test_column_iterator, TYPES>();
}

template<class Mat>
struct test_rows
{
	void
	operator()() const
	{
		auto m = create_mat<Mat>();

		auto r = m.rows();
		auto c = m.columns();

		for (uint i = 0; i < r; ++i) {
			auto row = m.row(i);
			for (uint j = 0; j < c; ++j) {
				REQUIRE(row[j] == m[i][j]);
				row[j] = typename Mat::value_type();
				REQUIRE(m[i][j] == typename Mat::value_type());
			}
		}
	}
};

TEST_CASE("linalg/matrix: row returns a reference to the given row in the given matrix", "[linalg]")
{
	invoke_for_each_type<test_rows, TYPES>();
}

template<class Mat>
struct test_cols
{
	void
	operator()() const
	{
		auto m = create_mat<Mat>();

		auto r = m.rows();
		auto c = m.columns();

		for (uint j = 0; j < c; ++j) {
			auto col = m.column(j);
			for (uint i = 0; i < r; ++i) {
				REQUIRE(col[i] == m[i][j]);
				col[i] = typename Mat::value_type();
				REQUIRE(m[i][j] == typename Mat::value_type());
			}
		}
	}
};

TEST_CASE("linalg/matrix: column returns a reference to the given row in the given matrix", "[linalg]")
{
	invoke_for_each_type<test_cols, TYPES>();
}
