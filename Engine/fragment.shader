#version 330

in vec3 colorToFragmentShader;

out vec4 FragColor;

void main()
{
    FragColor = vec4(colorToFragmentShader, 1.0);
}
