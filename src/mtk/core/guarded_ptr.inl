#include <mtk/core/guarded_ptr.hpp>

namespace mtk {
namespace impl_core {

void
throw_nullptr_exception() noexcept(false)
{
	throw nullptr_exception();
}

}

const char*
nullptr_exception::what() const noexcept
{
	return "nullptr exception";
}

// namespace impl_core
} // namespace mtk
