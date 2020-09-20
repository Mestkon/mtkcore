#ifndef MTK_CORE_GUARDED_PTR_HPP
#define MTK_CORE_GUARDED_PTR_HPP

//! @file
//! Contains the guarded_ptr structure.

namespace mtk {
namespace impl_core {
[[noreturn]]
void
throw_nullptr_exception() noexcept(false);
} // namespace impl_core

//! @defgroup guarded_ptr mtk/core/guarded_ptr.hpp
//! @{

//! @brief Thrown by guarded_ptr when accessing a nullptr.
//!
//! This does not inherit from std::exception as it should be inconvenient to
//! catch because the user should put in explicit guards before dereferencing
//! instead of relying on exceptions.
//!
//! @sa guarded_ptr
struct nullptr_exception { };

//! @brief A light-weight non-owning pointer replacement
//! which throws nullptr_exception if nullptr is dereferenced.
//!
//!	Supports implicit conversion from and to T*.
//!
//! @sa nullptr_exception
//! @sa pointer
template<class T>
class guarded_ptr
{
public:
	//! Initializes the pointer to nullptr.
	constexpr
	guarded_ptr() noexcept :
		m_ptr(nullptr)
	{ }

	//! @brief Initializes the pointer to the given pointer.
	//!
	//! @pre The given pointer must be a valid pointer or nullptr.
	constexpr
	guarded_ptr(T* ptr) noexcept :
		m_ptr(ptr)
	{ }

	//! Replaces the current pointer.
	constexpr
	guarded_ptr&
	operator=(T* rhs) noexcept { m_ptr = rhs; return *this; }

	//! Returns the current pointer.
	constexpr
	operator T*() const noexcept { return m_ptr; }

	//! @brief Dereferences the pointer. Throws nullptr_exception if the current
	//! pointer is nullptr.
	//!
	//! @pre The currently contained pointer must either point to a valid
	//! object or be nullptr.
	constexpr
	T&
	operator*() const { this->_verify(); return *m_ptr; }

	//! @brief Returns the pointer. Throws nullptr_exception if the current
	//! pointer is nullptr.
	//!
	//! @pre The currently contained pointer must either point to a valid
	//! object or be nullptr.
	constexpr
	T*
	operator->() const { this->_verify(); return m_ptr; }

private:
	constexpr
	void
	_verify() const
	{
		if (!m_ptr)
			mtk::impl_core::throw_nullptr_exception();
	}

	T* m_ptr;
};

//! @}

} // namespace mtk

#endif
