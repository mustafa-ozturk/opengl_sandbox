#include "orthographic_camera.h"

orthographic_camera::orthographic_camera(float left, float right, float bottom, float top)
    : m_projection_matrix(glm::ortho(left, right, bottom, top, -1.0f, 1.0f)),
      m_view_matrix(1.0f)
{
    m_projection_view_matrix = m_projection_matrix * m_view_matrix;
}

void orthographic_camera::recalculate_view_matrix()
{
    glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_position)
                        * glm::rotate(glm::mat4(1.0f), m_rotation, glm::vec3(0, 0, 1));

    m_view_matrix = glm::inverse(transform);
    m_projection_view_matrix = m_projection_matrix * m_view_matrix;
}
