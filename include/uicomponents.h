#ifndef UICOMPONENTS_H_
#define UICOMPONENTS_H_

typedef struct {
    float x, y;
} vec2_t;
typedef struct {
    float x, y, z;
} vec3_t;
typedef struct {
    float x, y, z, w;
} vec4_t;

typedef struct {
    vec2_t pos;
    vec2_t size;
    vec4_t color;
} rect_t;

typedef struct {
    vec2_t font_size;
    vec4_t font_color;
    char *text;
} text_t;

typedef struct {
    rect_t base;
    text_t text;
} lbl_t;

enum BTN_STATE {
    REST,
    HOVERED,
    PRESSED,
    HELD,
    RELEASED,
};

typedef struct {
    rect_t base;
    vec4_t rest_col, hov_col, press_col;
    int state;
    void (*onclick)(void);
    text_t text;
} btn_t;

extern rect_t **rect_list;
extern int rect_list_len;
extern lbl_t **lbl_list;
extern int lbl_list_len;
extern btn_t **btn_list;
extern int btn_list_len;

void terminate_uicomponents();
void set_btn_state(btn_t *btn, int state);
void init_btn(btn_t *btn);
void init_lbl(lbl_t *lbl);
void init_rect(rect_t *rect);
void init_uicomponents();

#endif