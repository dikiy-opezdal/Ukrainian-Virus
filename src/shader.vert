#version 330 core

layout(location=0) in vec2 a_pos;
layout(location=1) in vec2 a_texcoord;

uniform vec2 u_offset;
uniform vec2 u_size;
uniform vec2 u_resolution;

out vec2 v_texcoord;

void main() {
    gl_Position = vec4((a_pos * u_size + u_offset - u_resolution / 2.0) * 2.0 / u_resolution * vec2(1.0, -1.0), 0.0, 1.0);
    v_texcoord = a_texcoord;
}