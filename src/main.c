#include <stdio.h>
#include <stdlib.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <renderer.h>
#include <uicomponents.h>

rect_t footer;
btn_t yes_btn, no_btn, cancel_btn;

void terminate() {
    terminate_renderer();
    terminate_uicomponents();
    running = 0;
}

void toggle_flag() {
    running = 0;
}

int init() {
    if (!init_renderer()) {
        return -1;
    }
    init_uicomponents();

    init_rect(&footer);
    init_btn(&yes_btn);
    init_btn(&no_btn);
    init_btn(&cancel_btn);

    footer.size = (vec2_t){scr_width, scr_height * 0.27f};
    footer.pos.y = scr_height - footer.size.y;
    footer.color = (vec3_t){0.94f, 0.94f, 0.94f};

    cancel_btn.base.pos = (vec2_t){scr_width - cancel_btn.base.size.x - 10.0f, scr_height - cancel_btn.base.size.y - (footer.size.y - cancel_btn.base.size.y) / 2.0f + 2.0f};
    cancel_btn.onclick = &toggle_flag;
    cancel_btn.text = "Cancel";

    no_btn = cancel_btn;
    no_btn.base.pos.x -= no_btn.base.size.x + 10.0f;
    no_btn.text = "No";

    yes_btn = no_btn;
    yes_btn.base.pos.x -= yes_btn.base.size.x + 10.0f;
    yes_btn.text = "Yes";

    return 1;
}

int main() {
    if (!init()) {
        terminate();
        return -1;
    }

    while(running && !glfwWindowShouldClose(window)) {
        render();
    }

    terminate();
    return 0;
}