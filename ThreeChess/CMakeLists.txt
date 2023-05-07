cmake_minimum_required(VERSION 2.8.0)
set(PROJECT_NAME threechess)
project(${PROJECT_NAME})
add_executable(${PROJECT_NAME} main.c BoardAction.c GameControl.c)