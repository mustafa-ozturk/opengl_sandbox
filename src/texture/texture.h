#pragma once

#include <iostream>

#include <GL/glew.h>
#include "stb_image/stb_image.h"


class texture
{
public:
    texture(const std::string& path);
    ~texture();

    void bind(unsigned int slot = 0) const;
    void unbind();

    int get_width() const { return m_width; }
    int get_height() const { return m_height; }
    unsigned int get_texture_id() const { return m_texture_id; }
private:
    unsigned int m_texture_id;
    std::string m_filepath;
    unsigned char* m_local_texture_buffer;
    int m_width;
    int m_height;
    int m_bytes_per_pixel;
};
