#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <unordered_map>

#include <GL/glew.h>

#include "glm/glm.hpp"


class shader
{
public:
    shader(const std::string& vertex_shader_filepath, const std::string& fragment_shader_filepath);
    ~shader();

    void bind() const;
    void unbind() const;

    void set_uniform_4f(const std::string& name, float v0, float v1, float v2, float v3);
    void set_uniform_1f(const std::string& name, float value);
    void set_uniform_1i(const std::string& name, int value);
    void set_unifrom_mat4f(const std::string& name, const glm::mat4& matrix);

    unsigned int get_shader_id() const { return m_shader_id; }
private:
    // compile given shader code and test it, return the shader ID
    unsigned int compile_shader(unsigned int type, const std::string& source);
    // create a shader program that is linked and validated, return the shader program ID
    unsigned int create_shader(const std::string& vertexShader, const std::string& fragmentShader);

    GLint get_uniform_location(const std::string& name) const;
private:
    std::string m_vertex_shader_filepath;
    std::string m_fragment_shader_filepath;
    unsigned int m_shader_id;
    mutable std::unordered_map<std::string, int> m_uniform_location_cache;
};
