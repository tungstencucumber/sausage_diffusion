cmake_minimum_required(VERSION 3.16)
project(Diffusion_graphics_engine)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Diffusion_graphics_engine
        main.cpp
        particle.cpp
        particle.h
        Circle.cpp
        Circle.h
        Vector2D.cpp
        Vector2D.h
        DrawableParticle.cpp DrawableParticle.h)

set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR "SFML-2.5.1/lib/cmake/SFML")

find_package(SFML 2.5.1 COMPONENTS graphics audio system window REQUIRED)
target_link_libraries(Diffusion_graphics_engine sfml-system sfml-window sfml-graphics sfml-audio)