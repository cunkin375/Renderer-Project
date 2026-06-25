#version 460 core

out vec4 FragColor;

void main()
{
    // vec2 uv = (gl_FragCoord * 2.0 - u_resolution.xy) / u_resolution.y;
    //
    // float d = length(uv);

    // float mask  = sin(d*11)
    FragColor = vec4(1.0f, 0.2f, 1.0f, 1.0f);
}
