
set(PROJECT_NAME e3d_core)
project(${PROJECT_NAME})

set(src_root_path "${CMAKE_CURRENT_SOURCE_DIR}")

file(
        GLOB_RECURSE source_list
        LIST_DIRECTORIES false
        RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}"
        "${src_root_path}/*.*"
)

add_library(${PROJECT_NAME} ${source_list})

target_link_libraries(${PROJECT_NAME}
        easy3d::core
        easy3d::renderer
        easy3d::viewer
        easy3d::util
        easy3d::gui
        third_party
        3rd_imgui
)

target_include_directories(${PROJECT_NAME}
        PUBLIC third_party
        ${src_root_path}
        ${src_root_path}/3rdParty
        ${src_root_path}/math
        ${src_root_path}/math/algorithm
        ${src_root_path}/math/common
        ${src_root_path}/math/geometry
        ${src_root_path}/math/math
        ${src_root_path}/element
        ${src_root_path}/utils
        ${src_root_path}/viewer
        ${src_root_path}/action
)

target_include_directories(${PROJECT_NAME}
        PRIVATE ${PROJECT_SOURCE_DIR}
)