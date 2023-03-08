#pragma once

#include <vector>
#include <cstring>
#include <array>

#include <GL/glew.h>
#include <glm/glm.hpp>
#include "glm/gtc/matrix_transform.hpp"
#include "imgui/imgui.h"

#include "vertex.h"
#include "test_utility/test.h"
#include "shader/shader.h"
#include "texture/texture.h"
#include "batch_renderer/batch_renderer.h"
#include "gl_check_error/gl_check_error.h"


namespace test {
    class test_batch_dynamic_geometry : public test
    {
    public:
        test_batch_dynamic_geometry();
        ~test_batch_dynamic_geometry() override;

        void on_render() override;
        void on_imgui_render() override;
        std::string get_test_name() override { return "Batch Rendered Dynamic Geometry"; };
    private:
        std::vector<GLuint> m_indices;

        GLuint m_vertex_array_object;
        GLuint m_vertex_buffer_object;
        GLuint m_index_buffer_object;

        float m_quad_position[2] = {100.0f, 100.0f};

        shader* m_shader;
        texture* m_texture_christmas_tree;
        texture* m_texture_snowman;
    };
}
