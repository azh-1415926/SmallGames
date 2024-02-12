cmake_minimum_required(VERSION 2.8.0)
project(FiveInARow)

aux_source_directory(src srcs)

add_executable(${PROJECT_NAME} ${srcs})
target_include_directories(${PROJECT_NAME} PRIVATE include)