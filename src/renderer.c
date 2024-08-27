#include <stdio.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <shaders.h>
#include <uicomponents.h>

#include <renderer.h>

float scr_width = 500.0f;
float scr_height = 200.0f;

GLFWwindow *window;

unsigned int shader_program;

int running;

void terminate_renderer() {
    glfwTerminate();
}

void draw_rect(rect_t *rect) {
    glUniform2f(glGetUniformLocation(shader_program, "u_offset"), rect->pos.x, rect->pos.y);
    glUniform2f(glGetUniformLocation(shader_program, "u_size"), rect->size.x, rect->size.y);
    glUniform3f(glGetUniformLocation(shader_program, "u_color"), rect->color.x, rect->color.y, rect->color.z);

    glDrawArrays(GL_TRIANGLES, 0, 6);
}

void draw_btn(btn_t *btn) {
    draw_rect(&btn->base);
}

void render() {
    glfwPollEvents();

    glClear(GL_COLOR_BUFFER_BIT);
    for (int i = 0; i < rect_list_len; i++) draw_rect(rect_list[i]);
    for (int i = 0; i < btn_list_len; i++) draw_btn(btn_list[i]);

    glfwSwapBuffers(window);
}

void init_buffers() {
    float vertex_data[] = {
        0.0f,  1.0f,
        0.0f,  0.0f,
        1.0f,  0.0f,
        1.0f,  0.0f,
        1.0f,  1.0f,
        0.0f,  1.0f,
    };

    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_data), vertex_data, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glUniform2f(glGetUniformLocation(shader_program, "u_resolution"), scr_width, scr_height);
}

void cursor_position_callback(GLFWwindow *window, double x, double y) {
    for (int i = 0; i < btn_list_len; i++) {
        btn_t *btn = btn_list[i];
        vec2_t pos0 = btn->base.pos;
        vec2_t pos1 = {pos0.x + btn->base.size.x, pos0.y + btn->base.size.y};

        if ((x > pos0.x && y > pos0.y) && (x < pos1.x && y < pos1.y)) {
            if (btn->state != HOVERED && btn->state != HELD && btn->state != PRESSED) {
                set_btn_state(btn, HOVERED);
            }
            break;
        }
        else if (btn->state == HOVERED || btn->state == HELD || btn->state == PRESSED) {
            set_btn_state(btn, REST);
            break;
        }
    }
}
void mouse_button_callback(GLFWwindow *window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        if (action == GLFW_PRESS) {
            for (int i = 0; i < btn_list_len; i++) {
                btn_t *btn = btn_list[i];
                if (btn->state == HOVERED) {
                    set_btn_state(btn, PRESSED);
                    break;
                }
            }
        }
        if (action == GLFW_RELEASE) {
            for (int i = 0; i < btn_list_len; i++) {
                btn_t *btn = btn_list[i];
                if (btn->state == HELD || btn->state == PRESSED) {
                    set_btn_state(btn, RELEASED);
                    break;
                }
            }
        }
    }
}

int init_window() {
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, 0);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, 1);
#endif

    window = glfwCreateWindow(scr_width, scr_height, "Virus Alert !", NULL, NULL);
    if (window == NULL) {
        printf("Failed to create GLFW window");
        return -1;
    }
    glfwMakeContextCurrent(window);

    glfwSetCursorPosCallback(window, cursor_position_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        printf("Failed to init GLAD");
        return -1;
    }

    glViewport(0, 0, scr_width, scr_height);

    return 1;
}

int init_renderer() {
    if (!init_window()) {
        return -1;
    }

    shader_program = create_shader_program("src/shader.vert", "src/shader.frag");
    glUseProgram(shader_program);

    init_buffers();

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    running = 1;

    return 1;
}