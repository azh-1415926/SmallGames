cmake_minimum_required(VERSION 2.8.0)
project(TestForChessBoard)

aux_source_directory(src srcs)

add_executable(${PROJECT_NAME} ${srcs})
target_link_libraries(${PROJECT_NAME} PRIVATE MODULES)