#ifndef RENDERER_H_
#define RENDERER_H_

extern float scr_width, scr_height;
extern GLFWwindow *window;
extern int stop_flag;

int init_renderer();
void render();
void terminate_renderer();

#endif