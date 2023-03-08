cmake_minimum_required(VERSION 3.24)
project(opengl_sandbox)

set(CMAKE_CXX_STANDARD 23)

include_directories(src)
include_directories(tests)
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
        src/vertex.h
        src/gl_check_error/gl_check_error.h
        src/gl_check_error/gl_check_error.cpp
        src/shader/shader.h
        src/shader/shader.cpp
        src/texture/texture.h
        src/texture/texture.cpp
        src/batch_renderer/batch_renderer.cpp
        src/batch_renderer/batch_renderer.h
        tests/test_utility/test.h
        tests/test_utility/test_menu.h
        tests/test_utility/test_menu.cpp
        tests/test_single_triangle/test_single_triangle.h
        tests/test_single_triangle/test_single_triangle.cpp
        tests/test_multiple_triangles/test_multiple_triangles.h
        tests/test_multiple_triangles/test_multiple_triangles.cpp
        tests/test_single_quad_texture/test_single_quad_texture.h
        tests/test_single_quad_texture/test_single_quad_texture.cpp
        tests/test_batch_quad_texture/test_batch_quad_texture.cpp
        tests/test_batch_quad_texture/test_batch_quad_texture.h
        tests/test_sandbox/test_sandbox.cpp
        tests/test_sandbox/test_sandbox.h
        tests/test_batch_dynamic_geometry/test_batch_dynamic_geometry.cpp
        tests/test_batch_dynamic_geometry/test_batch_dynamic_geometry.h
)

find_package ( OpenGL REQUIRED )
target_link_libraries(opengl_sandbox OpenGL::GL )

find_package ( glfw3 REQUIRED )
target_link_libraries(opengl_sandbox glfw )

find_package ( GLEW REQUIRED )
target_link_libraries(opengl_sandbox GLEW::GLEW )