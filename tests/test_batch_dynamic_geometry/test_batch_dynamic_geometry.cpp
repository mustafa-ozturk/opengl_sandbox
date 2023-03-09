#include "test_batch_dynamic_geometry.h"

test::test_batch_dynamic_geometry::test_batch_dynamic_geometry()
        : m_vertex_array_object(0),
          m_vertex_buffer_object(0),
          m_index_buffer_object(0),
          m_shader(nullptr),
          m_texture_christmas_tree(nullptr),
          m_texture_snowman(nullptr)
{
    // enable blending
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // pattern
    // 0, 1, 2, 2, 3, 0,
    // 4, 5, 6, 6, 7, 4
    // 4 verticies per quad
    // 100 quads = 400 verticies
    for (int i = 0; i < m_max_index_count; i++)
    {
        m_indices.push_back(i);
        m_indices.push_back(i + 1);
        m_indices.push_back(i + 2);

        m_indices.push_back(i + 2);
        m_indices.push_back(i + 3);
        m_indices.push_back(i);
        i+=3;
    }

    glGenVertexArrays(1, &m_vertex_array_object);
    glBindVertexArray(m_vertex_array_object);

    glGenBuffers(1, &m_vertex_buffer_object);
    glBindBuffer(GL_ARRAY_BUFFER, m_vertex_buffer_object);
    // allocate vertex buffer without copying data
    glBufferData(GL_ARRAY_BUFFER, m_max_vertex_count * sizeof(vertex), nullptr, GL_DYNAMIC_DRAW);

    // vertex positions
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (const void*)offsetof(vertex, position));
    // texture coordinates
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(vertex), (const void*)offsetof(vertex, texture_coordinate));
    // texture id
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, sizeof(vertex), (const void*)offsetof(vertex, texture_id));

    glGenBuffers(1, &m_index_buffer_object);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_index_buffer_object);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(unsigned int), m_indices.data(), GL_STATIC_DRAW);

    m_shader = new shader("assets/shaders/batch_rendered_textures/vertex.glsl",
                          "assets/shaders/batch_rendered_textures/fragment.glsl");
    m_texture_christmas_tree = new texture("assets/textures/christmas_tree.png");
    m_texture_snowman = new texture("assets/textures/snowman.png");

    glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));
    glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));
    glm::mat4 proj = glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f);
    glm::mat4 mvp = proj * view * model;
    m_shader->bind();
    m_shader->set_unifrom_mat4f("u_MVP", mvp);

    // bind the textures to the right slots
    m_texture_christmas_tree->bind(0);
    m_texture_snowman->bind(1);

    int samplers[2] = { 0, 1};
    glUniform1iv(m_shader->get_uniform_location("u_Textures"), 2, samplers);
}

test::test_batch_dynamic_geometry::~test_batch_dynamic_geometry()
{
    glDeleteVertexArrays(1, &m_vertex_array_object);
    glDeleteBuffers(1, &m_vertex_buffer_object);
    glDeleteBuffers(1, &m_index_buffer_object);
    delete m_shader;
    delete m_texture_christmas_tree;
    delete m_texture_snowman;
}

void test::test_batch_dynamic_geometry::on_render()
{
    auto q0 = batch_renderer::create_quad(m_quad_position[0], m_quad_position[1], 0.0f, 100.0f);
    auto q1 = batch_renderer::create_quad(500.0f, 100.0f, 1.0f, 100.0f);

    vertex verticies[8];
    // memcyp copies q.size() * sizeof(vertex) bytes from q.data() into verticies
    memcpy(verticies, q0.data(), q0.size() * sizeof(vertex));
    memcpy(verticies + q0.size(), q1.data(), q1.size() * sizeof(vertex));

    // set dynamic vertex buffer
    glBindBuffer(GL_ARRAY_BUFFER, m_vertex_buffer_object);
    // sends data to vertex buffer without doing any allocations
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(verticies), verticies);

    gl_check_error();

    glBindVertexArray(m_vertex_array_object);
    glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, nullptr);

    gl_check_error();
}

void test::test_batch_dynamic_geometry::on_imgui_render()
{
    ImGui::DragFloat2("Quad 0 Position", m_quad_position, 1.0f);
}
