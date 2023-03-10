#pragma once

#include <glm/glm.hpp>
#include "glm/gtc/matrix_transform.hpp"

class orthographic_camera
{
public:
    orthographic_camera(float left, float right, float bottom, float top);

    const glm::vec3& get_position() const { return m_position; }
    float get_rotation() const { return m_rotation; }
    const glm::mat4& get_projection_matrix() const { return m_projection_matrix; }
    const glm::mat4& get_view_matrix() const { return m_view_matrix; }
    const glm::mat4 get_projection_view_matrix() const { return m_projection_view_matrix; }

    void set_position(const glm::vec3& position) { m_position = position; recalculate_view_matrix();}
    void set_rotation(float rotation) { m_rotation = rotation; recalculate_view_matrix();} // z axis rotation
private:
    void recalculate_view_matrix();
private:
    glm::mat4 m_projection_matrix;
    glm::mat4 m_view_matrix;
    glm::mat4 m_projection_view_matrix;

    glm::vec3 m_position = { 0.0f, 0.0f, 0.0f };
    float m_rotation = 0.0f;
};
