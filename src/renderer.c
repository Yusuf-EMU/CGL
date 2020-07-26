#include <stdlib.h>
#include <GL/glew.h>
#include "include/renderer.h"
#include "include/main.h"
#include "include/logger.h"

extern logger_T* LOGGER;

color_T* color(float r, float g, float b, float a) {
    color_T* color = calloc(1, sizeof(struct COLOR));
    color->r = r;
    color->g = g;
    color->b = b;
    color->a = a;   
}

renderer_T* init_renderer() {
    if(glewInit() != GLEW_OK)
        fatal(LOGGER, "Failed to initialize GLEW");
    
    renderer_T* renderer = calloc(1, sizeof(struct RENDERER));
    renderer->color = color(0.0f, 0.0f, 0.0f, 1.0f);
}

void set_renderer_color(renderer_T* renderer, color_T* color) {
    renderer->color = color;
}

void clear_view(renderer_T* renderer) {
    glClearColor(renderer->color->r, renderer->color->g, renderer->color->b, renderer->color->a);
    glClear(GL_COLOR_BUFFER_BIT);
}

void draw_elements(renderer_T* renderer, GLsizei count) {
    glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, NULL);
}

void fill_quad(renderer_T* renderer, int x, int y, int width, int height) {

}