
cmake_minimum_required(VERSION 3.12)
set(CMAKE_CXX_STANDARD 17)
get_filename_component(PROJECT_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)
project(bvh_viewer)


set(src_root_path "${CMAKE_CURRENT_SOURCE_DIR}")

file(
        GLOB_RECURSE source_list
        LIST_DIRECTORIES false
        RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}"
        "${src_root_path}/*.*"
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_executable(${PROJECT_NAME}
        ${source_list}
)

target_link_libraries(${PROJECT_NAME}
        3rd_imgui
        third_party
        easy3d::core
        easy3d::renderer
        easy3d::viewer
        easy3d::util
        easy3d::gui
        e3d_core
)
target_include_directories(bvh_viewer PRIVATE ${PROJECT_SOURCE_DIR})