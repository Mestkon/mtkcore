#include <mtk/core/guarded_ptr.hpp>

namespace mtk {
namespace impl_core {

void
throw_nullptr_exception() noexcept(false)
{
	throw nullptr_exception();
}

} // namespace impl_core
} // namespace mtk
