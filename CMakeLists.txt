cmake_minimum_required(VERSION 3.16)
project(sausage_diffusion)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(sausage_diffusion
        main.cpp
        particle.cpp
        particle.h
        Circle.cpp
        Circle.h
        Vector2D.cpp
        Vector2D.h
        DrawableParticle.cpp
        DrawableParticle.h)

set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR "SFML-2.5.1/lib/cmake/SFML")

find_package(SFML 2.5.1 COMPONENTS graphics audio system window REQUIRED)
target_link_libraries(sausage_diffusion sfml-system sfml-window sfml-graphics sfml-audio)