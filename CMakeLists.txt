cmake_minimum_required(VERSION 3.12)
project(edit_3d_platform)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")

add_subdirectory(easy3d)
add_subdirectory(third_party)
add_subdirectory(src)
