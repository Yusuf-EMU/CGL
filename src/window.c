#include <stdlib.h>
#include <GLFW/glfw3.h>
#include "include/logger.h"
#include "include/window.h"

extern logger_T* LOGGER;

window_T* init_window(int width, int height, char* title, int fullscreen, int refresh_rate) {
    window_T* window = calloc(1, sizeof(struct WINDOW));

    if(glfwInit() == GLFW_FALSE)
        fatal(LOGGER, "Failed to initialize GLFW");

    if(fullscreen){
        const GLFWvidmode* vidmode = glfwGetVideoMode(glfwGetPrimaryMonitor());
        glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
        width = vidmode->width;
        height = vidmode->height;
    }

    window->window_id = glfwCreateWindow(width, height, title, NULL, NULL); 
    glfwHideWindow(window->window_id);
    glfwMakeContextCurrent(window->window_id);

    window->refresh_rate = refresh_rate;
    window->visible = FALSE;
    window->width = width;
    window->height = height;
    window->title = title;
    window->fullscreen = fullscreen;
}

void dispose_window(window_T* window) {
    glfwDestroyWindow(window->window_id);
    free(window);
}

void dispose_glfw_session() {
    glfwTerminate();
}

void update_window(window_T* window) {
    glfwSwapBuffers(window->window_id);
    glfwPollEvents();
}

void set_window_visible(window_T* window, int visible) {
    if(visible) {
        glfwShowWindow(window->window_id);
        window->visible = TRUE;
        return;
    }
    glfwHideWindow(window->window_id);
    window->visible = FALSE;
}

int window_should_close(window_T* window) {
    return glfwWindowShouldClose(window->window_id);
}