#pragma once

#include <vector>

#include <GL/glew.h>
#include <glm/glm.hpp>
#include "glm/gtc/matrix_transform.hpp"

#include "test_utility/test.h"
#include "shader/shader.h"
#include "texture/texture.h"


namespace test
{
    class test_single_quad_texture : public test
    {
    public:
        test_single_quad_texture();
        ~test_single_quad_texture() override;

        void on_render() override;
        void on_imgui_render() override;
        std::string get_test_name() override { return "Single Quad Texture"; };
    private:
        std::vector<GLfloat> m_verticies;
        std::vector<GLuint> m_indices;

        GLuint m_vertex_array_object;
        GLuint m_vertex_buffer_object;
        GLuint m_index_buffer_object;

        shader* m_shader;
        texture* m_texture;
    };
}