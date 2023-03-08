#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include "test_utility/test_menu.h"
#include "test_sandbox/test_sandbox.h"
#include "test_single_triangle/test_single_triangle.h"
#include "test_multiple_triangles/test_multiple_triangles.h"
#include "test_single_quad_texture/test_single_quad_texture.h"
#include "test_batch_quad_texture/test_batch_quad_texture.h"
#include "test_batch_dynamic_geometry/test_batch_dynamic_geometry.h"

#include "gl_check_error/gl_check_error.h"

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720
#define GLSL_VERSION "#version 400"

int main()
{
    // Initialize glfw
    if (!glfwInit())
    {
        return -1;
    }

    GLFWwindow* p_window;

    // glfw hints
    {
        // create the openGL context with the core profile with version 4.0
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        // needed for mac
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    }

    // glfw pWindow and opengl context
    {
        // Create a windowed mode Window and its OpenGL context */
        p_window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "opengl_sandbox", nullptr, nullptr);
        if (!p_window)
        {
            glfwTerminate();
            return -1;
        }
        // Make the Window's context current
        glfwMakeContextCurrent(p_window);

        // syncronize fps with monitor refresh rate
        glfwSwapInterval(1);
    }

    // init glew
    if (glewInit() != GLEW_OK)
    {
        std::cout << "[GLEW INIT ERROR]" << std::endl;
    }

    // opengl stats
    {
        std::cout << "OPENGL VERSION: " << glGetString(GL_VERSION) << std::endl;
        GLint texture_units;
        glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &texture_units);
        std::cout << "TEXTURE UNITS: " << texture_units  << std::endl;
        std::cout << "--------------------------------------" << std::endl;
    }

    // setup imgui
    {
        // Setup Dear ImGui context
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();

        // Setup Dear ImGui style
        ImGui::StyleColorsDark();

        // Setup Platform/Renderer backends
        ImGui_ImplGlfw_InitForOpenGL(p_window, true);
        ImGui_ImplOpenGL3_Init(GLSL_VERSION);
    }

    // setup tests
    test::test* p_current_test = nullptr;
    auto* p_test_menu = new test::test_menu(p_current_test);
    p_current_test = p_test_menu;

    // register tests
    {
        p_test_menu->register_test<test::test_sandbox>("Sandbox");
        p_test_menu->register_test<test::test_single_triangle>("Single Triangle");
        p_test_menu->register_test<test::test_multiple_triangles>("Multiple Triangles (Individual Draw Calls)");
        p_test_menu->register_test<test::test_single_quad_texture>("Single Quad Texture");
        p_test_menu->register_test<test::test_batch_quad_texture>("Batch Rendered Quad Textures");
        p_test_menu->register_test<test::test_batch_dynamic_geometry>("Batch Rendered Dynamic Geometry");

        std::cout << "--------------------------------------" << std::endl;
    }

    gl_check_error();

    while (!glfwWindowShouldClose(p_window))
    {
        // set clear color and clear color buffer
        {
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        }

        // start ImGui Frame
        {
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();
        }

        // run tests
        if (p_current_test){
            p_current_test->on_render();
            ImGui::Begin("Tests");
            if (p_current_test != p_test_menu && ImGui::Button("<-"))
            {
                delete p_current_test;
                p_current_test = p_test_menu;
            }
            if (p_current_test != p_test_menu)
            {
                ImGui::Text("Test: %s", p_current_test->get_test_name().c_str());
            }
            p_current_test->on_imgui_render();
            ImGui::End();
            gl_check_error();
        }

        // render ImGui Frame
        {
            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        }

        // swap front and back buffers and Poll for process events
        {
            glfwSwapBuffers(p_window);
            glfwPollEvents();
        }
        gl_check_error();
    }

    // cleanup
    {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();

        glfwDestroyWindow(p_window);
        glfwTerminate();
    }

    return 0;
}
