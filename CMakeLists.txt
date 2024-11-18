cmake_minimum_required(VERSION 3.15)
project(asteroids)

set(CMAKE_C_STANDARD 11)

file(GLOB SOURCES "${CMAKE_SOURCE_DIR}/src/*.c")
add_executable(${PROJECT_NAME} ${SOURCES})

include(FetchContent)

FetchContent_Declare(
  raylib
  URL https://github.com/raysan5/raylib/archive/refs/tags/5.0.tar.gz
)
FetchContent_GetProperties(raylib)
if (NOT raylib_POPULATED)
  set(FETCHCONTENT_QUIET NO)
  FetchContent_Populate(raylib)

  set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples

  add_subdirectory(${raylib_SOURCE_DIR} ${raylib_BINARY_DIR})
endif()
target_link_libraries(${PROJECT_NAME} raylib)

FetchContent_Declare(
  raygui
  URL https://github.com/raysan5/raygui/archive/refs/tags/4.0.tar.gz
)
FetchContent_GetProperties(raygui)
if (NOT raygui_POPULATED)
  set(FETCHCONTENT_QUIET NO)
  FetchContent_Populate(raygui)

  set(BUILD_RAYGUI_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples

  add_subdirectory(${raygui_SOURCE_DIR}/projects/CMake ${raygui_BINARY_DIR})
endif()
target_link_libraries(${PROJECT_NAME} raygui)

if (APPLE)
  target_link_libraries(${PROJECT_NAME} "-framework IOKit")
  target_link_libraries(${PROJECT_NAME} "-framework Cocoa")
  target_link_libraries(${PROJECT_NAME} "-framework OpenGL")
endif()

