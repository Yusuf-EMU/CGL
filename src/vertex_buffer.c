#include <stdlib.h>
#include "include/vertex_buffer.h"
#include "include/logger.h"
#include "include/main.h"

extern logger_T* LOGGER;

vertex_buffer_T* vertex_buffer(float* positions, int count, int dimensions) {
    vertex_buffer_T* vertex_buffer = calloc(1, sizeof(struct VERTEX_BUFFER));
    
    glGenBuffers(1, &vertex_buffer->id);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer->id);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * count, positions, GL_STATIC_DRAW);
    glVertexAttribPointer(0, dimensions, GL_FLOAT, GL_FALSE, sizeof(float) * dimensions, 0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    return vertex_buffer;
};

void set_vertex_buffer_data(vertex_buffer_T* vertex_buffer, float* positions, int count) {
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer->id);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * count, positions, GL_DYNAMIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void bind_vertex_buffer(vertex_buffer_T* vertex_buffer) {
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer == NULL ? 0 : vertex_buffer->id);
}