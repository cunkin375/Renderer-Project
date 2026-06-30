#version 460 core

out vec4 frag_color;
in vec3 model_color;

void main()
{
    frag_color = vec4(model_color, 1.0);
}
