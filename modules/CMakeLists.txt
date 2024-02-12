project(MODULES)

file(GLOB_RECURSE srcs CONFIGURE_DEPENDS src/*.c include/*.h)

add_library(${PROJECT_NAME} STATIC ${srcs})
target_include_directories(${PROJECT_NAME} PUBLIC include)

add_subdirectory(Qt)