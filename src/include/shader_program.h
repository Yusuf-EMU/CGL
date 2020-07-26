#ifndef SHADER_PROGRAM_H
#define SHADER_PROGRAM_H

#include <GL/glew.h>

typedef struct SHADER_PROGRAM
{
    GLuint id;
} shader_program_T;

shader_program_T* create_program_from_files(const char* vertex_shader_path, const char* fragment_shader_path);

#endif