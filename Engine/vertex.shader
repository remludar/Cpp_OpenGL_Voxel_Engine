#version 330

layout (location = 0) in vec3 vertexPosition;
layout (location = 1) in vec3 vertexColor;

uniform mat4 fullTransformMatrix;

out vec3 colorToFragmentShader;

void main()
{
	gl_Position = fullTransformMatrix * vec4(vertexPosition, 1.0);
	colorToFragmentShader = vertexColor;
}