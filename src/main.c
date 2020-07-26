#include <stdlib.h>
#include <GL/glew.h>
#include "include/logger.h"
#include "include/window.h"
#include "include/renderer.h"
#include "include/vertex_buffer.h"
#include "include/index_buffer.h"
#include "include/shader_program.h"

#include "include/stb_image.h"
#include <cglm/cglm.h>
#include <cglm/mat4.h>

logger_T* LOGGER;
window_T* WINDOW;
renderer_T* RENDERER;

void terminate(int exitcode) {
    free(RENDERER);
    
    dispose_glfw_session();

    info(LOGGER, "Terminated gracefully");
    free(LOGGER);
    
    exit(exitcode);
}

int main(int argc, char* argv) {
    //Init various behaviour handler structs
    LOGGER = init_logger();
    WINDOW = init_window(100, 100, "CGL Test", FALSE, 60);
    RENDERER = init_renderer();

    info(LOGGER, "CGL Initialized");

    //Window setup
    set_renderer_color(RENDERER, color(1.0f, 0.0f, 1.0f, 1.0f));
    set_window_visible(WINDOW, TRUE);

    float vertices[8] = {
        0.0f, 0.0f,
        1.0f, 0.0f,
        0.0f, 1.0f,
		1.0f, 1.0f
    };

	int indices[6] = {
		0, 1, 2,
		1, 2, 3
	};

    vertex_buffer_T* vb = vertex_buffer(vertices, 8, 2);
	index_buffer_T* ib = index_buffer(indices, 6);
	
    shader_program_T* shader_program = create_program_from_files("./res/shaders/vert.vert", "./res/shaders/frag.frag");
    
	
	GLuint texture;
	int width, height, nrChannels;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	stbi_set_flip_vertically_on_load(1);
	stbi_uc *data = stbi_load("./res/img/temp.jpg", &width, &height, &nrChannels, 0);
	if(data)
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	else
		error(LOGGER, "Failed to load texture");
	stbi_image_free(data);

/*
    mat4 projection;
    glm_perspective(glm_rad(45.0f), 100 / 100, 0.1f, 100.0f, projection);
	float convert_proj[16];
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            convert_proj[(i) + j] = projection[i][j];
        }
    }
*/
	//Window/Draw Loop
    while(!window_should_close(WINDOW)) {
        clear_view(RENDERER);

        //Testing dynamic draw
        //vertices[0] -= 0.01f;
        //set_vertex_buffer_data(vb, vertices, 8);

		bind_index_buffer(ib);
		bind_vertex_buffer(vb);
		glUniform3f(glGetUniformLocation(shader_program->id, "rotation"), 0.0f, 0.0f, 0.0f);
		glUniform3f(glGetUniformLocation(shader_program->id, "scale"), 1.0f, 1.0f, 0.0f);
        glUniform3f(glGetUniformLocation(shader_program->id, "translation"), 0.0f, 0.0f, 0.0f);
//        glUniformMatrix4fv(glGetUniformLocation(shader_program->id, "projection"), 1, GL_FALSE, projection);
		draw_elements(RENDERER, ib->count);
        
        update_window(WINDOW);
    }

    dispose_window(WINDOW);

    //Exit properly
    terminate(0);
}