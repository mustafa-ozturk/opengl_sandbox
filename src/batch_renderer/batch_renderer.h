#pragma once

#include <array>

#include "vertex.h"

namespace batch_renderer {
    std::array<vertex, 4> create_quad(float x, float y, float textureID, float size);
}