#ifndef INDEX_BUFFER_H
#define INDEX_BUFFER_H

#include <GL/glew.h>

typedef struct INDEX_BUFFER {
    GLuint id;
    GLsizei count;
} index_buffer_T;

index_buffer_T* index_buffer(GLuint* indices, GLsizei count);

void set_index_buffer_data(index_buffer_T* index_buffer, GLuint* positions, GLsizei count);

void bind_index_buffer(index_buffer_T* index_buffer);

#endif