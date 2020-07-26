#ifndef RENDERERGL_H
#define RENDERERGL_H

typedef struct COLOR 
{
    float r;
    float g;
    float b;
    float a;
} color_T;

color_T* color(float r, float g, float b, float a);

typedef struct RENDERER
{
    color_T* color;
} renderer_T;

renderer_T* init_renderer();

void set_renderer_color(renderer_T* renderer, color_T* color);

void clear_view(renderer_T* renderer);

void draw_elements(renderer_T* renderer, GLsizei count);

void fill_quad(renderer_T* renderer, int x, int y, int width, int height);

#endif