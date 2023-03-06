#include "test_multiple_triangles.h"

test::test_multiple_triangles::test_multiple_triangles()
    :   m_vertex_array_object(0),
        m_vertex_buffer_object(0),
        m_index_buffer_object(0),
        m_shader(nullptr),
        m_view(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0))),
        m_proj(glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f))
{
    m_verticies = {
             // x,       y,    z,
             0.0f,   50.0f, 0.0f,   // A, i: 0
             50.0f, -50.0f, 0.0f,   // B, i: 1
            -50.0f, -50.0f, 0.0f    // C, i: 2
    };
    m_indices = {
            0, 1, 2,
    };

    glGenVertexArrays(1, &m_vertex_array_object);
    glBindVertexArray(m_vertex_array_object);

    glGenBuffers(1, &m_vertex_buffer_object);
    glBindBuffer(GL_ARRAY_BUFFER, m_vertex_buffer_object);
    glBufferData(GL_ARRAY_BUFFER, m_verticies.size() * sizeof(float), m_verticies.data(), GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    glGenBuffers(1, &m_index_buffer_object);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_index_buffer_object);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(unsigned int), m_indices.data(), GL_STATIC_DRAW);

    m_shader = new shader("assets/shaders/basic_color/basic_vertex_shader.glsl",
                          "assets/shaders/basic_color/basic_fragment_shader.glsl");
    m_shader->bind();
}


test::test_multiple_triangles::~test_multiple_triangles()
{
    delete m_shader;
}

void test::test_multiple_triangles::on_render()
{
    glBindVertexArray(m_vertex_array_object);

    {
        glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(160, 270, 0));
        glm::mat4 mvp = m_proj * m_view * model;
        m_shader->set_unifrom_mat4f("u_MVP", mvp);
        glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, nullptr);
    }
    {
        glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(320, 270, 0));
        glm::mat4 mvp = m_proj * m_view * model;
        m_shader->set_unifrom_mat4f("u_MVP", mvp);
        glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, nullptr);
    }
    {
        glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(480, 270, 0));
        glm::mat4 mvp = m_proj * m_view * model;
        m_shader->set_unifrom_mat4f("u_MVP", mvp);
        glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, nullptr);
    }
    {
        glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(640, 270, 0));
        glm::mat4 mvp = m_proj * m_view * model;
        m_shader->set_unifrom_mat4f("u_MVP", mvp);
        glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, nullptr);
    }
    {
        glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(800, 270, 0));
        glm::mat4 mvp = m_proj * m_view * model;
        m_shader->set_unifrom_mat4f("u_MVP", mvp);
        glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, nullptr);
    }
}

void test::test_multiple_triangles::on_imgui_render()
{
}
