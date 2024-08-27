#ifndef RENDERER_H_
#define RENDERER_H_

extern float scr_width, scr_height;
extern GLFWwindow *window;
extern int running;

void terminate_renderer();
void render();
int init_renderer();

#endif