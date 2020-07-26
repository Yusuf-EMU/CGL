#ifndef WINDOW_H
#define WINDOW_H

#include <GLFW/glfw3.h>

#define FALSE 0
#define TRUE 1

typedef struct WINDOW
{
    GLFWwindow* window_id;

    char* title;
    int width;
    int height;

    int fullscreen;
    int visible;
    int refresh_rate;
} window_T;

window_T* init_window(int width, int height, char* title, int fullscreen, int refresh_rate);

void dispose_window(window_T* window);

void dispose_glfw_session();

void update_window(window_T* window);

void set_window_visible(window_T* window, int visible);

int window_should_close(window_T* window);

#endif