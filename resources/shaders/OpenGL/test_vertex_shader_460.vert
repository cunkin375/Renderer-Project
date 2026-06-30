#version 460 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
// uniform mat4 translation;

out vec3 model_color;

void main()
{
    gl_Position = projection * view * model * vec4(position, 1.0);
    model_color = color;
}

