#version 430 core
layout(location = 0) in vec3 aPos;
layout(std140, binding = 0) uniform UniformBuffer {
    vec3 direction;
    vec4 color;
    mat4 model;
};

uniform mat4 projection_view;
// uniform mat4 model;
// uniform vec3 direction;
// uniform vec4 color;

out vec4 ourColor;
void main() {
    // gl_Position =  model * vec4(aPos, 1.0);
    gl_Position = projection_view * model * vec4(aPos * direction, 1.0);
    ourColor = color;
}