#include "test_batch_rendered_quad_texture.h"

test::test_batch_rendered_quad_texture::test_batch_rendered_quad_texture()
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

    m_verticies = {
            // x, y, z, s, t, tex_id
            50.0f,  150.0f, 0.0f, 0.0f, 1.0f, 0.0f,      // 0
            150.0f, 150.0f, 0.0f, 1.0f, 1.0f, 0.0f,      // 1
            50.0f,   50.0f, 0.0f, 0.0f, 0.0f, 0.0f,      // 2
            150.0f,  50.0f, 0.0f, 1.0f, 0.0f, 0.0f,      // 3

            200.0f, 150.0f, 0.0f, 0.0f, 1.0f, 1.0f,      // 4
            300.0f, 150.0f, 0.0f, 1.0f, 1.0f, 1.0f,      // 5
            200.0f,  50.0f, 0.0f, 0.0f, 0.0f, 1.0f,      // 6
            300.0f,  50.0f, 0.0f, 1.0f, 0.0f, 1.0f,      // 7
    };
    m_indices = {
            0, 1, 2, 1, 2, 3,
            4, 5, 6, 5, 6, 7
    };

    glGenVertexArrays(1, &m_vertex_array_object);
    glBindVertexArray(m_vertex_array_object);

    glGenBuffers(1, &m_vertex_buffer_object);
    glBindBuffer(GL_ARRAY_BUFFER, m_vertex_buffer_object);
    glBufferData(GL_ARRAY_BUFFER, m_verticies.size() * sizeof(float), m_verticies.data(), GL_STATIC_DRAW);

    // vertex positions
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), nullptr);
    // texture coordinates
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (const void*) (3 * sizeof(float)));
    // texture id
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (const void*) (5 * sizeof(float)));

    glGenBuffers(1, &m_index_buffer_object);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_index_buffer_object);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(unsigned int), m_indices.data(), GL_STATIC_DRAW);

    m_shader = new shader("assets/shaders/batch_rendered_textures/batch_rendered_texture_vertex_shader.glsl",
                          "assets/shaders/batch_rendered_textures/batch_rendered_texture_fragment_shader.glsl");
    m_shader->bind();

    glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));
    glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));
    glm::mat4 proj = glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f);
    glm::mat4 mvp = proj * view * model;

    m_shader->set_unifrom_mat4f("u_MVP", mvp);

    m_texture_christmas_tree = new texture("assets/textures/christmas_tree.png");
    m_texture_snowman = new texture("assets/textures/snowman.png");

    int samplers[2] = { 0, 1};
    glUniform1iv(m_shader->get_uniform_location("u_Textures"), 2, samplers);
}

test::test_batch_rendered_quad_texture::~test_batch_rendered_quad_texture()
{
    delete m_shader;
    delete m_texture_christmas_tree;
    delete m_texture_snowman;
}

void test::test_batch_rendered_quad_texture::on_render()
{
    // bind the textures to the right slots
    m_texture_christmas_tree->bind(0);
    m_texture_snowman->bind(1);

    glBindVertexArray(m_vertex_array_object);
    glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, nullptr);
}

void test::test_batch_rendered_quad_texture::on_imgui_render()
{

}
