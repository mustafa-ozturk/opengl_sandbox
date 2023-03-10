#pragma once

#include <vector>

#include <GL/glew.h>
#include <glm/glm.hpp>
#include "glm/gtc/matrix_transform.hpp"

#include "test_utility/test.h"
#include "shader/shader.h"
#include "orthographic_camera/orthographic_camera.h"

namespace test
{
    class test_orthographic_camera : public test
    {
    public:
        test_orthographic_camera();
        ~test_orthographic_camera() override;

        void on_render() override;
        void on_imgui_render() override;
        std::string get_test_name()  { return "Orthographic Camera"; };
    private:
        std::vector<GLfloat> m_verticies;
        std::vector<GLuint> m_indices;

        GLuint m_vertex_array_object;
        GLuint m_vertex_buffer_object;
        GLuint m_index_buffer_object;

        orthographic_camera m_orthographic_camera;

        shader* m_shader;
    };
}