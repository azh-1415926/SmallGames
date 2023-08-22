cmake_minimum_required(VERSION 3.5) # CMake install : https://cmake.org/download/
project(2048_Qt LANGUAGES CXX)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_PREFIX_PATH "D:/Qt/6.5.0/mingw_64") # Qt Kit Dir
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_PREFIX_PATH "D:/Qt/6.5.0/mingw_64")
set(ROOT_DIR ../)

find_package(Qt6 COMPONENTS Widgets REQUIRED) # Qt COMPONENTS

aux_source_directory(./src srcs)
aux_source_directory(${ROOT_DIR}/component components)

# Specify MSVC UTF-8 encoding   
add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")

add_executable(${PROJECT_NAME}
    # WIN32 # If you need a terminal for debug, please comment this statement
    ${srcs}
    ${components}
) 
target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Widgets) # Qt5 Shared Library
target_include_directories(${PROJECT_NAME} PRIVATE ${ROOT_DIR}/component)