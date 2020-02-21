cmake_minimum_required(VERSION 3.0)

project(invasivespeciescpp LANGUAGES C)

add_executable(invasivespeciescpp main.c)

install(TARGETS invasivespeciescpp RUNTIME DESTINATION bin)
