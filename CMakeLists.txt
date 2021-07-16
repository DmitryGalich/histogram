cmake_minimum_required(VERSION 3.10)

set(PROJECT_TITLE words_histogram_creator)
project(${PROJECT_TITLE} LANGUAGES CXX VERSION 1.0)

find_package(GTest 1.10 REQUIRED)
find_package(Qt5 COMPONENTS Core Quick QuickControls2 Charts REQUIRED)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options(-Wall -Wextra -pedantic -Werror)

add_subdirectory(libs)
add_subdirectory(apps)
