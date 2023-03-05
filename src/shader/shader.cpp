#include "shader.h"

shader::shader(const std::string& vertex_shader_filepath, const std::string& fragment_shader_filepath)
    : m_vertex_shader_filepath(vertex_shader_filepath), m_fragment_shader_filepath(fragment_shader_filepath), m_shader_id(0)
{
    std::cout << "loading vertex shader at filepath: " << vertex_shader_filepath << std::endl;
    std::cout << "loading fragment shader at filepath: " << fragment_shader_filepath << std::endl;

    std::ifstream vs_stream(vertex_shader_filepath);
    std::stringstream vs_buffer;
    vs_buffer << vs_stream.rdbuf();

    std::ifstream fs_stream(fragment_shader_filepath);
    std::stringstream fs_buffer;
    fs_buffer << fs_stream.rdbuf();

    this->m_shader_id = create_shader(vs_buffer.str(), fs_buffer.str());
}

shader::~shader()
{
    glDeleteProgram(m_shader_id);
}

void shader::bind() const
{
    glUseProgram(m_shader_id);
}

void shader::unbind() const
{
    glUseProgram(0);
}

void shader::set_uniform_4f(const std::string& name, float v0, float v1, float v2, float v3)
{
    glUniform4f(get_uniform_location(name), v0, v1, v2, v3);
}

void shader::set_uniform_1f(const std::string& name, float value)
{
    glUniform1f(get_uniform_location(name), value);
}

void shader::set_uniform_1i(const std::string& name, int value)
{
    glUniform1i(get_uniform_location(name), value);
}

void shader::set_unifrom_mat4f(const std::string& name, const glm::mat4& matrix)
{
    glUniformMatrix4fv(get_uniform_location(name), 1, GL_FALSE, &matrix[0][0]);
}

unsigned int shader::compile_shader(unsigned int type, const std::string& source)
{
    // create a shader object, it returns the ID of that shader
    unsigned int shader_object_id = glCreateShader(type);

    const char* src = source.c_str();

    // replace the source code in a shader object
    glShaderSource(shader_object_id, 1, &src, nullptr);

    // compile a shader object, takes the id of the shader object you want to compile
    glCompileShader(shader_object_id);

    // error handling
    int result;
    // returns a parameter from a shader object, in this case the compile status
    glGetShaderiv(shader_object_id, GL_COMPILE_STATUS, &result);
    // if shader compilation failed
    if (result == GL_FALSE)
    {
        // shader did not compile successfuly
        int length;
        // query the error message length
        glGetShaderiv(shader_object_id, GL_INFO_LOG_LENGTH, &length);
        // dynamically allocate on the stack with alloca, create string with the size of that length
        // this is a dynamically allocated char array on the stack
        char* message = (char*) alloca(length * sizeof(char));
        // query the the error message
        glGetShaderInfoLog(shader_object_id, length, &length, message);
        std::cout << "[SHADER ERROR]: Failed to compile "
                  << (type == GL_VERTEX_SHADER ? "VERTEX" : "FRAGMENT")
                  << " shader"
                  << std::endl
                  << message
                  << std::endl;
        glDeleteShader(shader_object_id);
        return 0;
    }

    return shader_object_id;
}

unsigned int shader::create_shader(const std::string& vertexShader, const std::string& fragmentShader)
{
    // create a program, it returns the ID of the program
    unsigned int program = glCreateProgram();

    unsigned int vs = compile_shader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = compile_shader(GL_FRAGMENT_SHADER, fragmentShader);

    // attach the shader object to a program object
    glAttachShader(program, vs);
    glAttachShader(program, fs);

    // link our program
    glLinkProgram(program);
    // validate that our program can run
    glValidateProgram(program);

    // delete the shader objects since they are already attached, linked and validated
    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}

GLint shader::get_uniform_location(const std::string& name) const
{
    // check if we already used glGetUniformLocation with name, if yes return the the location ID
    if (m_uniform_location_cache.find(name) != m_uniform_location_cache.end())
        return m_uniform_location_cache[name];

    GLint location = glGetUniformLocation(m_shader_id, name.c_str());

    if (location == -1)
        std::cout << "Warning: uniform '" << name << "' doesn't exist!" << std::endl;

    m_uniform_location_cache[name] = location;

    return location;
}
