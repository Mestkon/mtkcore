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
  include/mtk/core/preprocessor.hpp
  include/mtk/core/saturated_integer.hpp
  include/mtk/core/scope_guard.hpp
  include/mtk/core/type_traits.hpp
  include/mtk/core/types.hpp

  src/mtk/core/assert.cpp
  src/mtk/core/math.cpp
  src/mtk/core/scope_guard.cpp
)
