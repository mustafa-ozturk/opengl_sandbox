#pragma once

#include <glm/glm.hpp>
#include "glm/gtc/matrix_transform.hpp"

struct vertex
{
    glm::vec3 position;
    glm::vec4 color;
    glm::vec2 texture_coordinate;
    float texture_id;
};