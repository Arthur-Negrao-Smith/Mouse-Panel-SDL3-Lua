cmake_minimum_required(VERSION 3.5)
project(mouse_menu "CXX")

set(CMAKE_CXX_STANDARD 23)

find_package(SDL3 REQUIRED CONFIG)
find_package(SDL3_ttf CONFIG REQUIRED)

#
file(GLOB_RECURSE SRC_FILES "src/*.cpp")

# create the executable
add_executable(${PROJECT_NAME} ${SRC_FILES})

target_include_directories(${PROJECT_NAME} PRIVATE
  src
  src/ui
)

target_link_libraries(${PROJECT_NAME} PRIVATE SDL3_ttf::SDL3_ttf SDL3::SDL3)
