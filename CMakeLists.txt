cmake_minimum_required(VERSION 3.24)
project(opengl_sandbox)

set(CMAKE_CXX_STANDARD 23)

include_directories(vendor)

add_executable(opengl_sandbox
        vendor/stb_image/stb_image.cpp
        vendor/imgui/imgui.cpp
        vendor/imgui/imgui_draw.cpp
        vendor/imgui/imgui_impl_glfw.cpp
        vendor/imgui/imgui_impl_opengl3.cpp
        vendor/imgui/imgui_tables.cpp
        vendor/imgui/imgui_widgets.cpp
        src/main.cpp
)

find_package ( OpenGL REQUIRED )
target_link_libraries(opengl_sandbox OpenGL::GL )

find_package ( glfw3 REQUIRED )
target_link_libraries(opengl_sandbox glfw )

find_package ( GLEW REQUIRED )
target_link_libraries(opengl_sandbox GLEW::GLEW )