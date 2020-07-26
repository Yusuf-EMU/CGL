#include <stdio.h>
#include <stdlib.h>
#include "include/logger.h"
#include "include/shader_program.h"
#include "include/main.h"

extern logger_T* LOGGER;

void read_file(const char* path, char** dest) {
    FILE *file;
    long size_in_bytes;
    
    file = fopen(path, "r");
    
    if(file == NULL) {
        error(LOGGER, "Requested file is invalid");
        exit(-1);
    }
    
    fseek(file, 0L, SEEK_END);
    size_in_bytes = ftell(file);
    
    fseek(file, 0L, SEEK_SET);	
    
    *dest = malloc(size_in_bytes);
    
    if(*dest == NULL) {
        error(LOGGER, "Failed to allocate file-read-buffer. Out of memory?");
        exit(-1);
    }
    
    fread(*dest, sizeof(char), size_in_bytes, file);
    fclose(file);
};

GLuint compile_shader(const GLchar* data, GLenum type) {
    GLuint id = glCreateShader(type);
    glShaderSource(id, 1, &data, NULL);
    glCompileShader(id);

    GLuint result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if(result == GL_FALSE) {
        GLsizei length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        GLchar message[length];
        glGetShaderInfoLog(id, length, &length, message);
        error(LOGGER, message);
        error(LOGGER, type == GL_VERTEX_SHADER ? "Vertex Shader" : "Fragment Shader");
        error(LOGGER, data);
        glDeleteShader(id);
        return 0;
    }

    return id;
}

GLuint create_shader(const GLchar* vert, const GLchar* frag) {
    GLuint program = glCreateProgram();

    GLuint vertShd = compile_shader(vert, GL_VERTEX_SHADER);
    GLuint fragShd = compile_shader(frag, GL_FRAGMENT_SHADER);

    glAttachShader(program, vertShd);
    glAttachShader(program, fragShd);
    glLinkProgram(program);
    glValidateProgram(program);

    glDetachShader(program, fragShd);
    glDeleteShader(fragShd);
    glDetachShader(program, vertShd);
    glDeleteShader(vertShd);

    return program;
}

shader_program_T* create_program_from_files(const char* vertex_shader_path, const char* fragment_shader_path) {
    shader_program_T* program = calloc(1, sizeof(struct SHADER_PROGRAM));

    char* vs;
    char* fs;
    read_file(vertex_shader_path, &vs);
    read_file(fragment_shader_path, &fs);
    program->id = create_shader(vs, fs);
    free(vs);
    free(fs);

    glUseProgram(program->id);

    return program;
}