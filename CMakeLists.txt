cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)

# Set the project name
project(HeliosRT)

set (   SOURCE
    src/main.cpp
    src/camera.hpp
    src/color.hpp
    src/is_hittable.hpp
    src/ray.hpp
    src/interval.hpp
    src/common.hpp
    src/sphere.hpp
    src/hittable_list.hpp
    src/material.hpp
    src/vector.hpp
)

# Add the executable
add_executable(helios ${SOURCE})