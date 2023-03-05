#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

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
        ImGui_ImplOpenGL3_Init((char*) glGetString(GL_NUM_SHADING_LANGUAGE_VERSIONS));
    }

    // setup tests here

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

        // run tests here

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
    }

    // cleanup
    {
        glfwTerminate();
    }

    return 0;
}
