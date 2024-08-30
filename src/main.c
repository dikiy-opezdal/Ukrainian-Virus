#include <stdio.h>
#include <stdlib.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <renderer.h>
#include <uicomponents.h>

lbl_t alert_lbl;
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
    init_lbl(&alert_lbl);
    init_btn(&yes_btn);
    init_btn(&no_btn);
    init_btn(&cancel_btn);

    footer.size = (vec2_t){scr_width, scr_height * 0.27f};
    footer.pos.y = scr_height - footer.size.y;

    alert_lbl.base.pos = (vec2_t){(scr_width - alert_lbl.base.size.x) / 2.0f, (scr_height - footer.size.y - alert_lbl.base.size.y) / 2.0f};
    alert_lbl.text.text = "Hi, I am an Albanian virus but because of poor technology in my country unfortunately I am not able to harm your computer. Please be so kind to delete one of your important files yourself and then forward me to other users. Many thanks for your cooperation! Best regards,Albanian virus";

    cancel_btn.base.pos = (vec2_t){scr_width - cancel_btn.base.size.x - 10.0f, scr_height - cancel_btn.base.size.y - (footer.size.y - cancel_btn.base.size.y) / 2.0f + 2.0f};
    cancel_btn.onclick = &toggle_flag;
    cancel_btn.text.text = "Cancel";

    no_btn = cancel_btn;
    no_btn.base.pos.x -= no_btn.base.size.x + 10.0f;
    no_btn.text.text = "No";

    yes_btn = no_btn;
    yes_btn.base.pos.x -= yes_btn.base.size.x + 10.0f;
    yes_btn.text.text = "Yes";

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