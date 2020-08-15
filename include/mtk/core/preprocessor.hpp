#ifndef MTK_CORE_PREPROCESSOR_HPP
#define MTK_CORE_PREPROCESSOR_HPP

//! @file
//! Contains common preprocessor macros.


namespace mtk {

//! @defgroup preproc mtk/core/preprocessor.hpp
//! @{

namespace impl_core {

template<class... Args>
void
no_op(Args&& ...) noexcept { }

} // namespace impl_core

//! Inserts a no-op statement.
#define MTK_NO_OP mtk::impl_global::no_op()

//! @brief Evaluates the given expressions. Can be used to mark several variables
//! as used.
//!
//! @code
//! int func(int i, float f, bool b) {
//!  MTK_IGNORE(i, f, b); //no warning for not using i, f, and b
//!
//!  //implementation does not use i, f, or b
//!  return 0;
//! }
//! @endcode
#define MTK_IGNORE(...) mtk::impl_global::no_op(__VA_ARGS__)

//! @brief Puts quotation marks on both sides of the given test.
//!
//! @code
//! MTK_STRINGIFY_TEST(Something); //evaluates to "Something";
//! @endcode
#define MTK_STRINGIFY_TEXT(X) #X
//! @brief Evaluates the given macro and puts quatation marks
//! around the result.
//!
//! If X is not a macro, evaluates to MTK_STRINGIFY_TEXT.
//!
//! @code
//! #define PI 3.14
//!
//! MTK_STRINGIFY(PI); //evaluates to "3.14"
//! MTK_STRINGIFY(Something); //evaluates to "Something"
//! @endcode
#define MTK_STRINGIFY(X) MTK_STRINGIFY_TEXT(X)

//! @brief Concatrenates A and B
//!
//! @code
//! MTK_CONCAT_TEXT(Something, Else); //evaluates to SomethingElse
//! @endcode
#define MTK_CONCAT_TEXT(A, B) A##B
//! @brief Evaluates to the given macros and concatenates the result.
//!
//! If A or B is not a macro, the parameter that is not a macro
//! will be concatenated with the evaluation of the macro.
//!
//! If neither is a macro, evaluates to MTK_CONCAT_TEXT.
//!
//! @code
//! #define FUN This_is_fun_
//! #define ANSWER 42
//!
//! MTK_CONCAT(FUN, ANSWER); //Evaluates to This_is_fun_42
//! MTK_CONCAT(The_answer_, ANSWER); //Evaluates to The_answer_42
//! MTK_CONCAT(FUN, cpp); //Evaluates to This_is_fun_cpp
//! MTK_CONCAT(I_like_, macros); //Evaluates to I_like_macros
//! @endcode
//!
#define MTK_CONCAT(A, B) MTK_CONCAT_TEXT(A, B)

//! @brief Implements noexcept, trailing return type, and body of a
//! single statement function.
//!
//! @code
//! //these function templates are equivalent
//!
//! template<class Cont>
//! auto size_of_container(const Cont& c) MTK_RETURNS(c.size())
//!
//! template<class Cont>
//! auto size_of_container2(const Cont& c) noexcept(noexcept(c.size())) -> decltype(c.size()) {
//!  return c.size();
//! }
//! @endcode
#define MTK_RETURNS(X) noexcept(noexcept(X)) -> decltype(X) { return X; }

//! @}

} // namespace mtk

#endif
