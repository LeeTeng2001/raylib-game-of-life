cmake_minimum_required(VERSION 3.20)
project(game-of-life)

set(CMAKE_CXX_STANDARD 17)
find_package(raylib REQUIRED)

add_executable(${PROJECT_NAME} src/main.cpp src/gameOfLife.hpp src/config.hpp src/render.hpp)
target_link_libraries(${PROJECT_NAME} raylib)
