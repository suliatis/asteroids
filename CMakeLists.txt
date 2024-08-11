cmake_minimum_required(VERSION 3.15)
project(asteroids)

find_package(raylib 3.0 REQUIRED)

set(CMAKE_C_STANDARD 11)

file(GLOB SOURCES "${CMAKE_SOURCE_DIR}/src/*.c")
add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} raylib)

if (APPLE)
    target_link_libraries(${PROJECT_NAME} "-framework IOKit")
    target_link_libraries(${PROJECT_NAME} "-framework Cocoa")
    target_link_libraries(${PROJECT_NAME} "-framework OpenGL")
endif()

