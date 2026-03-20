cmake_minimum_required(VERSION 3.20)
project(MetaRender LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB_RECURSE METARENDER_SOURCES CONFIGURE_DEPENDS
  ${PROJECT_SOURCE_DIR}/src/*.cpp
)
file(GLOB_RECURSE METARENDER_HEADERS CONFIGURE_DEPENDS
  ${PROJECT_SOURCE_DIR}/src/*.hpp
)

# Windows-only sources
if (NOT WIN32)
  list(REMOVE_ITEM METARENDER_SOURCES
    ${PROJECT_SOURCE_DIR}/src/scenes/nehe/Lesson13.cpp
    ${PROJECT_SOURCE_DIR}/src/scenes/nehe/Lesson14.cpp
    ${PROJECT_SOURCE_DIR}/src/scenes/nehe/Lesson15.cpp
  )
endif()

add_library(metarender_engine STATIC
  ${METARENDER_SOURCES}
  ${METARENDER_HEADERS}
)

target_include_directories(metarender_engine PUBLIC
  ${PROJECT_SOURCE_DIR}/src
  ${PROJECT_SOURCE_DIR}/external/imgui
  ${PROJECT_SOURCE_DIR}/external/imgui/backends
)

add_executable(MetaRender
  src/app/main.cpp
)

add_custom_target(copy_assets
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/assets ${CMAKE_CURRENT_BINARY_DIR}/assets
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/config ${CMAKE_CURRENT_BINARY_DIR}/config
)
add_dependencies(MetaRender copy_assets)

find_package(glfw3 CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)
find_package(soil2 CONFIG REQUIRED)

add_library(imgui STATIC
  external/imgui/imgui.cpp
  external/imgui/imgui_draw.cpp
  external/imgui/imgui_tables.cpp
  external/imgui/imgui_widgets.cpp
  external/imgui/backends/imgui_impl_glfw.cpp
  external/imgui/backends/imgui_impl_opengl2.cpp
)

target_include_directories(imgui PUBLIC
  ${PROJECT_SOURCE_DIR}/external/imgui
  ${PROJECT_SOURCE_DIR}/external/imgui/backends
)

target_link_libraries(imgui PUBLIC glfw)

target_link_libraries(MetaRender PRIVATE
  metarender_engine
  glfw
  glad::glad
  imgui
  soil2
)

target_link_libraries(metarender_engine PUBLIC nlohmann_json::nlohmann_json)

if (WIN32)
  target_link_libraries(MetaRender PRIVATE opengl32)
endif()
