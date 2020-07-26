#ifndef VERTEX_BUFFER_H
#define VERTEX_BUFFER_H

#include <GL/glew.h>

typedef struct VERTEX_BUFFER {
    GLuint id;
} vertex_buffer_T;

vertex_buffer_T* vertex_buffer(float* positions, int count, int dimensions);

void set_vertex_buffer_data(vertex_buffer_T* vertex_buffer, float* positions, int count);

void bind_vertex_buffer(vertex_buffer_T* vertex_buffer);

#endif