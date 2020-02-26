cmake_minimum_required(VERSION 3.7)

project(InvasiveSpeciesCPP)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})
include_directories("${PROJECT_SOURCE_DIR}/include")
file(GLOB SOURCES "${PROJECT_SOURCE_DIR}/src/*.cpp")

add_executable(InvasiveSpeciesCPP apps/Main.cpp ${SOURCES})
target_link_libraries(InvasiveSpeciesCPP 
    SDL2::SDL2main
    SDL2::SDL2
)  
