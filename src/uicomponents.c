#include <stdio.h>
#include <stdlib.h>

#include <uicomponents.h>

rect_t **rect_list;
int rect_list_len;

btn_t **btn_list;
int btn_list_len;

void terminate_uicomponents() {
    free(rect_list);
    free(btn_list);
}

void set_btn_state(btn_t *btn, int state) {
    btn->state = state;

    switch (btn->state) {
        case REST:
            btn->base.color = btn->rest_col;
            break;
        case HOVERED:
            btn->base.color = btn->hov_col;
            break;
        case PRESSED:
            btn->base.color = btn->press_col;
            if (btn->onclick) {
                (*btn->onclick)();
            }
            btn->state = HELD;
            break;
        case RELEASED:
            set_btn_state(btn, HOVERED);
            break;
    }
}

void init_btn(btn_t *btn) {
    *btn = (btn_t){0};

    btn->rest_col = (vec3_t){0.85f, 0.85f, 0.85f};
    btn->hov_col = (vec3_t){0.8f, 0.8f, 0.8f};
    btn->press_col = (vec3_t){0.75f, 0.75f, 0.75f};

    btn->base.size = (vec2_t){85.0f, 25.0f};
    btn->base.color = btn->rest_col;
    btn->text = "Button";

    btn_list_len++;
    btn_list = (btn_t**)realloc(btn_list, btn_list_len * sizeof(btn_t*));
    btn_list[btn_list_len-1] = btn;
}

void init_rect(rect_t *rect) {
    *rect = (rect_t){0};

    rect->size = (vec2_t){100.0f, 100.0f};
    rect->color = (vec3_t){0.94f, 0.94f, 0.94f};

    rect_list_len++;
    rect_list = (rect_t**)realloc(rect_list, rect_list_len * sizeof(rect_t*));
    rect_list[rect_list_len-1] = rect;
}

void init_uicomponents() {
    rect_list = (rect_t**)calloc(0, sizeof(rect_t*));
    rect_list_len = 0;

    btn_list = (btn_t**)calloc(0, sizeof(btn_t*));
    btn_list_len = 0;
}