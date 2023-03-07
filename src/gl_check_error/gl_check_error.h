#pragma once

#include <iostream>
#include <GL/glew.h>

#define gl_check_error() gl_check_error_(__FILE__, __LINE__)

GLenum gl_check_error_(const char *file, int line);