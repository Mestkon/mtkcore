cmake_minimum_required(VERSION 3.5)

project (mtkcore LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(${CMAKE_PROJECT_NAME} STATIC "")
set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE include)

if(CMAKE_BUILD_TYPE MATCHES Debug)
    add_definitions(-DMTK_DEBUG)
endif()

target_sources(${CMAKE_PROJECT_NAME} PRIVATE
    include/mtk/core.hpp
    include/mtk/global.hpp
    include/mtk/core/allocator_traits.hpp
    include/mtk/core/assert.hpp
    include/mtk/core/casts.hpp
    include/mtk/core/container_traits.hpp
    include/mtk/core/flag_operators.hpp
    include/mtk/core/guarded_ptr.hpp
    include/mtk/core/iterator_traits.hpp
    include/mtk/core/math.hpp
    include/mtk/core/os.hpp
    include/mtk/core/preprocessor.hpp
    include/mtk/core/result.hpp
    include/mtk/core/saturated_integer.hpp
    include/mtk/core/scope_guard.hpp
    include/mtk/core/type_traits.hpp
    include/mtk/core/types.hpp

    src/mtk/core/assert.cpp
    src/mtk/core/guarded_ptr.cpp
    src/mtk/core/math.cpp
    src/mtk/core/result.cpp
    src/mtk/core/scope_guard.cpp
)

target_sources(${CMAKE_PROJECT_NAME} PRIVATE
    include/mtk/linalg.hpp
    include/mtk/linalg_fwd.hpp
    include/mtk/linalg/matrix.hpp
    include/mtk/linalg/matrix_base.hpp
    include/mtk/linalg/matrix_container_interface.hpp
    include/mtk/linalg/matrix_dynamic.hpp
    include/mtk/linalg/matrix_fixed.hpp
    include/mtk/linalg/matrix_interface.hpp
    include/mtk/linalg/matrix_partial_dynamic.hpp
    include/mtk/linalg/matrix_square_interface.hpp
    include/mtk/linalg/vector_interface.hpp

    src/mtk/linalg/matrix_det_and_inv.hpp
    src/mtk/linalg/matrix_dynamic_vector_reference.hpp
    src/mtk/linalg/matrix_fixed_vector_reference.hpp
    src/mtk/linalg/matrix_impl.hpp
    src/mtk/linalg/matrix_impl_fwd.hpp
    src/mtk/linalg/matrix_step_iterator.hpp
    src/mtk/linalg/matrix_vector_iterator.hpp
)
