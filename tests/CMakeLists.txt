cmake_minimum_required(VERSION 3.5)

project (mtkcore-tests LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(${CMAKE_PROJECT_NAME} main.cpp)
set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../include)

if(CMAKE_BUILD_TYPE MATCHES Debug)
    add_definitions(-DMTK_DEBUG)
endif()

target_sources(${CMAKE_PROJECT_NAME} PRIVATE
    core/allocator_traits.cpp
    core/casts.cpp
    core/container_traits.cpp
    core/flag_operators.cpp
    core/guarded_ptr.cpp
    core/iterator_traits.cpp
    core/math.cpp
    core/result.cpp
    core/saturated_integer.cpp
    core/scope_guard.cpp
    core/type_traits.cpp
    core/types.cpp
)
