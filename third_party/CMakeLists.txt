cmake_minimum_required(VERSION 3.12)
set(CMAKE_CXX_STANDARD 17)

get_filename_component(PROJECT_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)
project(third_party)

set(src_root_path "${CMAKE_CURRENT_SOURCE_DIR}")

file(
        GLOB_RECURSE source_list
        LIST_DIRECTORIES false
        RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}"
        "${src_root_path}/*.*"
)

add_library(${PROJECT_NAME} ${source_list})

target_include_directories(${PROJECT_NAME}
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)