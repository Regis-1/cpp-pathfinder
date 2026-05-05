cmake_minimum_required(VERSION 3.28)

project(
  pathfinder
  VERSION "0.1"
  LANGUAGES CXX
)

# library first
add_library(
  pathfinder STATIC
  src/Pathfinder.cpp
  src/Map.cpp
)

target_include_directories(
  pathfinder
  PUBLIC include
)

# visualizing application
add_executable(
  visualizer
  src/main.cpp
  src/Application.cpp
  src/Renderer.cpp
  src/Simulation.cpp
  src/UI.cpp
  src/Command.cpp
)

find_package(SDL3 REQUIRED)

add_library(
  imgui
  third_party/imgui/imgui.cpp
  third_party/imgui/imgui_draw.cpp
  third_party/imgui/imgui_tables.cpp
  third_party/imgui/imgui_widgets.cpp
  third_party/imgui/imgui_demo.cpp

  third_party/imgui/backends/imgui_impl_sdl3.cpp
  third_party/imgui/backends/imgui_impl_sdlrenderer3.cpp
)

target_include_directories(
  imgui
  PUBLIC
    third_party/imgui
    third_party/imgui/backends
)

target_link_libraries(
  imgui
  PUBLIC SDL3::SDL3
)

target_link_libraries(
  visualizer
  PRIVATE
    pathfinder
    SDL3::SDL3
    imgui
)
