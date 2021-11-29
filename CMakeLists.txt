cmake_minimum_required(VERSION 3.8)
project(simple_raytrace)

find_package(SDL2)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp Matrix.h Color.h Camera.cpp Camera.h Surface.cpp Surface.h Ray.cpp
        Ray.h Scene.cpp Scene.h LightSource.cpp LightSource.h Sphere.cpp Sphere.h Plane.cpp
        Plane.h RayTracer.cpp RayTracer.h Image.cpp Image.h)
include_directories(${SDL2_INCLUDE_DIRS})
add_executable(simple_raytrace ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})