#include "batch_renderer.h"


namespace batch_renderer {
    std::array<vertex, 4> create_quad(float x, float y, float textureID, float size)
    {
        vertex v0{};
        v0.position = {x, y, 0.0f};
        v0.texture_coordinate = {0.0f, 0.0f};
        v0.texture_id = textureID;

        vertex v1{};
        v1.position = {x, y + size, 0.0f};
        v1.texture_coordinate = {0.0f, 1.0f};
        v1.texture_id = textureID;

        vertex v2{};
        v2.position = {x + size, y + size, 0.0f};
        v2.texture_coordinate = {1.0f, 1.0f};
        v2.texture_id = textureID;

        vertex v3{};
        v3.position = {x + size, y, 0.0f};
        v3.texture_coordinate = {1.0f, 0.0f};
        v3.texture_id = textureID;

        return { v0, v1, v2, v3 };
    }
}