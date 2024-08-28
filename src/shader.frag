#version 330 core

in vec2 v_texcoord;

uniform vec4 u_color;
uniform float u_alpha;

uniform sampler2D u_texture;

out vec4 frag_color;

void main() {
    vec4 texel = texture(u_texture, v_texcoord);

    frag_color = vec4(
        mix(u_color.r, texel.r, u_alpha),
        mix(u_color.g, texel.g, u_alpha),
        mix(u_color.b, texel.b, u_alpha),
        mix(u_color.a, texel.a, u_alpha)
    );
}