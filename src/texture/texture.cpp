#include "texture.h"

texture::texture(const std::string& path)
    : m_texture_id(0),
      m_filepath(path),
      m_local_texture_buffer(nullptr),
      m_width(0),
      m_height(0),
      m_bytes_per_pixel(0)
{
    std::cout << "loading texture at filepath: " << path << std::endl;
    /* flips texture upside down, because opengl expects
     * texture pixels to start at the bottom left (0, 0)
     * (png specific)
     * */
    stbi_set_flip_vertically_on_load(1);
    /* load the texture into local buffer
     * desired_channels = 4, because we want RGBA
     * */
    m_local_texture_buffer = stbi_load(path.c_str(), &m_width, &m_height, &m_bytes_per_pixel, 4);

    // generate and bind texture
    glGenTextures(1, &m_texture_id);
    glBindTexture(GL_TEXTURE_2D, m_texture_id);

    // set texture params
    // ------------------
    // minification filter, how the texture will be resampled down if it needs to be rendered small
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    // magnification filter, how the texture will be resampled up if it needs to be rendered big
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


    // wrap mode ST = XY
    // ------------------
    // horizontal wrap, GL_CLAMP_TO_EDGE = don't extand the area
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    // vertical wrap, GL_CLAMP_TO_EDGE = don't extand the area
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    // send the data in local buffer to opengl (internalformat = opengl, format = format in buffer)
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_local_texture_buffer);

    // unbind the texture
    glBindTexture(GL_TEXTURE_2D, 0);

    if (m_local_texture_buffer)
    {
        stbi_image_free(m_local_texture_buffer);
    }
}

texture::~texture()
{
    glDeleteTextures(1, &m_texture_id);
}

void texture::bind(unsigned int slot) const
{
    // specify a texture slot
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, m_texture_id);
}

void texture::unbind()
{
    glBindTexture(GL_TEXTURE_2D, 0);
}
