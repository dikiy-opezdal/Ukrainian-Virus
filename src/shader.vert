#version 330 core

layout(location=0) in vec2 a_pos;
uniform vec2 u_offset;
uniform vec2 u_size;
uniform vec2 u_resolution;

void main() {
    gl_Position = vec4((a_pos * u_size + u_offset - u_resolution / 2.0) * 2.0 / u_resolution * vec2(1.0, -1.0), 0.0, 1.0);
}