#include <mtk/core/result.hpp>

namespace mtk {
namespace impl_core {

void
throw_bad_result_access()
{
	throw bad_result_access();
}

}

const char*
bad_result_access::what() const noexcept
{
	return "bad result access";
}

// namespace impl_core
} // namespace mtk
