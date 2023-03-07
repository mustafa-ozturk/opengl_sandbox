#include "gl_check_error.h"

GLenum gl_check_error_(const char *file, int line)
{
    GLenum errorCode;
    while ((errorCode = glGetError()) != GL_NO_ERROR)
    {
        std::string error;
        switch (errorCode)
        {
            // Set when an enumeration parameter is not legal.
            case GL_INVALID_ENUM:                  error = "INVALID_ENUM"; break;
                // Set when a value parameter is not legal.
            case GL_INVALID_VALUE:                 error = "INVALID_VALUE"; break;
                // Set when the state for a command is not legal for its given parameters.
            case GL_INVALID_OPERATION:             error = "INVALID_OPERATION"; break;
                // Set when a stack pushing operation causes a stack overflow.
            case GL_STACK_OVERFLOW:                error = "STACK_OVERFLOW"; break;
                // Set when a stack popping operation occurs while the stack is at its lowest point.
            case GL_STACK_UNDERFLOW:               error = "STACK_UNDERFLOW"; break;
                // Set when a memory allocation operation cannot allocate (enough) memory.
            case GL_OUT_OF_MEMORY:                 error = "OUT_OF_MEMORY"; break;
                // Set when reading or writing to a framebuffer that is not complete.
            case GL_INVALID_FRAMEBUFFER_OPERATION: error = "INVALID_FRAMEBUFFER_OPERATION"; break;
        }
        std::cout << "GLERROR: " << error << " | " << file << " (" << line << ")" << std::endl;
    }
    return errorCode;
}