cmake_minimum_required(VERSION 3.24)
project(opengl_sandbox)

set(CMAKE_CXX_STANDARD 23)

include_directories(vendor)

add_executable(opengl_sandbox src/main.cpp)

find_package ( OpenGL REQUIRED )
target_link_libraries(opengl_sandbox OpenGL::GL )

find_package ( glfw3 REQUIRED )
target_link_libraries(opengl_sandbox glfw )

find_package ( GLEW REQUIRED )
target_link_libraries(opengl_sandbox GLEW::GLEW )