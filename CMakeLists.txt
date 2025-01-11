cmake_minimum_required(VERSION 3.7)

project(SDL2Test)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_definitions(-std=c++17)

set(CXX_FLAGS "-g -Wall")
set(CMAKE_CXX_FLAGS "${CXX_FLAGS}")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")


find_package(SDL2 REQUIRED)
find_package(SDL2_ttf CONFIG)

if (SDL2_ttf_FOUND)
    message("Found cmake file for SDL2_ttf")
    set(SDL2_TTF_CMAKE_TARGET SDL2_ttf::SDL2_ttf)
else()
    message("Trying PkgConfig to find SDL2_ttf")
    find_package(PkgConfig)
    pkg_check_modules(SDL2_TTF REQUIRED SDL2_ttf)
    set(SDL2_TTF_CMAKE_TARGET "${SDL2_TTF_LDFLAGS}")
endif()
include_directories(${SDL2_INCLUDE_DIRS} src)

add_executable(SnakeGame src/main.cpp src/game.cpp src/controller.cpp src/renderer.cpp src/snake.cpp src/gamesetup.cpp)
string(STRIP ${SDL2_LIBRARIES} SDL2_LIBRARIES)
target_link_libraries(SnakeGame ${SDL2_LIBRARIES} ${SDL2_TTF_LIBRARIES})
