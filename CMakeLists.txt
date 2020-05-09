project(sausage_diffusion)

file(GLOB SOURCES "*.cpp")

add_executable(sausage_diffusion ${SOURCES})

set(CMAKE_CXX_FLAGS "-Wall -g")
OPTION(WITH_DEBUG_MODE "Build with debug mode" ON)
