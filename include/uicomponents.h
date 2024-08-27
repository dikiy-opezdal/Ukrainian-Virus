#ifndef UICOMPONENTS_H_
#define UICOMPONENTS_H_

typedef struct vec2_t {
    float x, y;
} vec2_t;
typedef struct vec3_t {
    float x, y, z;
} vec3_t;

typedef struct rect_t {
    vec2_t pos;
    vec2_t size;
    vec3_t color;
} rect_t;

enum BTN_STATE {
    REST,
    HOVERED,
    PRESSED,
    HELD,
    RELEASED,
};

typedef struct btn_t {
    rect_t base;
    vec3_t rest_col, hov_col, press_col;
    int state;
    void (*onclick)(void);
    char *text;
} btn_t;

extern rect_t **rect_list;
extern int rect_list_len;
extern btn_t **btn_list;
extern int btn_list_len;

void terminate_uicomponents();
void set_btn_state(btn_t *btn, int state);
void init_btn(btn_t *btn);
void init_rect(rect_t *rect);
void init_uicomponents();

#endif