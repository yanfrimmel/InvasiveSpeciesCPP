cmake_minimum_required(VERSION 3.7)

project(InvasiveSpeciesCPP)

find_package(SDL2 REQUIRED)
if (WIN32)
     find_package(SDL2IMAGE REQUIRED)
     find_package(SDL2TTF REQUIRED)
endif()

include_directories("${PROJECT_SOURCE_DIR}/assets" "${PROJECT_SOURCE_DIR}/include"
 ${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS} ${SDL2TTF_INCLUDE_DIRS})

if (WIN32)
     file(COPY "${PROJECT_SOURCE_DIR}/assets/" DESTINATION "Debug/assets/")
     file(COPY "${PROJECT_SOURCE_DIR}/assets/" DESTINATION "Release/assets/")
     file(COPY "${PROJECT_SOURCE_DIR}/lib/" DESTINATION "Release/")
     file(COPY "${PROJECT_SOURCE_DIR}/lib/" DESTINATION "Debug/")
endif()

file(COPY "${PROJECT_SOURCE_DIR}/assets/" DESTINATION "assets/")

file(GLOB SOURCES "${PROJECT_SOURCE_DIR}/src/*.cpp")
file(GLOB HEADERS "${PROJECT_SOURCE_DIR}/include/*.h")

add_executable(${PROJECT_NAME} apps/Main.cpp ${SOURCES} ${HEADERS} ${ASSETS})
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES} ${SDL2TTF_LIBRARIES})
target_compile_options(${PROJECT_NAME} PRIVATE
     $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>,$<CXX_COMPILER_ID:GNU>>:
          -Wall>
     $<$<CXX_COMPILER_ID:MSVC>:
          /W4>)

