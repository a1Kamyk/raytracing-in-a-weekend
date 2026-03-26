cmake_minimum_required(VERSION 3.12)
project(raytracer)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

set(SOURCES
        src/main.cpp
        src/Vec3.cpp
        src/Ray.cpp
        src/Hittable.cpp
        src/Sphere.cpp
        src/HittableList.cpp
        src/Plane.cpp
        src/Interval.cpp
        src/Camera.cpp
        src/Material.cpp
)

add_executable(raytracer ${SOURCES})

find_package(OpenMP REQUIRED)
if(OpenMP_CXX_FOUND)
    target_link_libraries(raytracer PUBLIC OpenMP::OpenMP_CXX)
endif()