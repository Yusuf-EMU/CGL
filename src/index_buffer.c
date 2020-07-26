#include <stdlib.h>
#include "include/index_buffer.h"
#include "include/logger.h"
#include "include/main.h"

extern logger_T* LOGGER;

index_buffer_T* index_buffer(GLuint* indices, GLsizei count) {
    index_buffer_T* index_buffer = calloc(1, sizeof(struct INDEX_BUFFER));
    
    index_buffer->count = count;

    glGenBuffers(1, &index_buffer->id);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer->id);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * count, indices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    return index_buffer;
};

void set_index_buffer_data(index_buffer_T* index_buffer, GLuint* indices, GLsizei count) {
    index_buffer->count = count;
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer->id);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * count, indices, GL_DYNAMIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void bind_index_buffer(index_buffer_T* index_buffer) {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer == NULL ? 0 : index_buffer->id);
}