cmake_minimum_required(VERSION 3.5)

project(ThreeChess VERSION 0.1 LANGUAGES CXX)

set(CMAKE_PREFIX_PATH "D:/Qt/6.5.0/mingw_64")

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 请自行填写 qt 工具链所在路径
# set(CMAKE_PREFIX_PATH "D:/Qt/6.5.0/mingw_64")

# 根目录
set(ROOT_DIR ../)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

aux_source_directory(./src srcs)
aux_source_directory(${ROOT_DIR}/component components)

add_executable(${PROJECT_NAME}
    # WIN32 # 若需要控制台调试可以注释这一条 # If you need a terminal for debug, please comment this statement
    ${srcs}
    ${components}
)
target_link_libraries(${PROJECT_NAME} PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_include_directories(${PROJECT_NAME} PRIVATE ${ROOT_DIR}/component)