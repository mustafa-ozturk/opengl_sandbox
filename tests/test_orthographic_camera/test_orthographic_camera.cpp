
#include "test_orthographic_camera.h"

test::test_orthographic_camera::test_orthographic_camera()
    : m_vertex_array_object(0),
      m_vertex_buffer_object(0),
      m_index_buffer_object(0),
      m_shader(nullptr),
      m_orthographic_camera(-1.6f, 1.6f, -0.9f, 0.9f)
{
    m_verticies = {
             // x,     y,    z
             0.0f,  0.5f, 0.0f,     // A, i: 0
             0.5f, -0.5f, 0.0f,     // B, i: 1
            -0.5f, -0.5f, 0.0f      // C, i: 2
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

    m_shader = new shader("assets/shaders/basic_color/vertex.glsl",
                          "assets/shaders/basic_color/fragment.glsl");
    m_shader->bind();


    // TODO: use WASDR to move camera
    m_orthographic_camera.set_position({0.5f, 0.5f, 0.0f});
    m_orthographic_camera.set_rotation(45.0f);
    glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));
    glm::mat4 mvp = m_orthographic_camera.get_projection_view_matrix() * model;
    m_shader->set_unifrom_mat4f("u_MVP", mvp);
}

test::test_orthographic_camera::~test_orthographic_camera()
{
    glDeleteVertexArrays(1, &m_vertex_array_object);
    glDeleteBuffers(1, &m_vertex_buffer_object);
    glDeleteBuffers(1, &m_index_buffer_object);
    delete m_shader;
}

void test::test_orthographic_camera::on_render()
{
    glBindVertexArray(m_vertex_array_object);
    glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, nullptr);
}

void test::test_orthographic_camera::on_imgui_render()
{
}
