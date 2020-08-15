#include <mtk/core/scope_guard.hpp>

#include <exception>

namespace mtk {
namespace impl_core {

int
uncaught_exceptions() noexcept
{
	return std::uncaught_exceptions();
}

} // namespace impl_core
} // namespace mtk
