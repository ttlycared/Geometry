cmake_minimum_required(VERSION 3.20)

project(GeometryBasic LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CLIPPER2_UTILS OFF CACHE BOOL "" FORCE)
set(CLIPPER2_EXAMPLES OFF CACHE BOOL "" FORCE)
set(CLIPPER2_TESTS OFF CACHE BOOL "" FORCE)
set(CLIPPER2_USINGZ OFF CACHE STRING "" FORCE)

add_subdirectory(
"${CMAKE_CURRENT_SOURCE_DIR}/../Clipper2/CPP"
"${CMAKE_CURRENT_BINARY_DIR}/Clipper2Build"
)

add_executable(
    GeometryBasic
    src/main.cpp
)

target_link_libraries(GeometryBasic PRIVATE Clipper2)