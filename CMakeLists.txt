cmake_minimum_required(VERSION 3.10)

project(sausage_diffusion)

file(GLOB SOURCES "*.cpp")

set(CMAKE_CXX_FLAGS "-Wall -g")

set(SFML_DIR "SFML-2.5.1/lib/cmake/SFML")

find_package(SFML 2.5 COMPONENTS graphics audio system REQUIRED)
add_executable(sausage_diffusion ${SOURCES})
target_link_libraries(sausage_diffusion sfml-graphics sfml-audio sfml-system)

OPTION(WITH_DEBUG_MODE "Build with debug mode" ON)
