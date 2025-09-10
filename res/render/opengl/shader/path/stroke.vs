#version 430 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec4 stroke_color;
uniform mat4 model;
uniform mat4 projection_view;

out vec4 ourColor;
void main() {
    // gl_Position =  model * vec4(aPos, 1.0);
    gl_Position = projection_view * model * vec4(aPos, 1.0);
    ourColor = stroke_color;
}