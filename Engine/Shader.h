#pragma once

#include <string>

#include <GL\glew.h>

enum ShaderType
{
	VERTEX_SHADER,
	FRAGMENT_SHADER
};

class Shader
{
public:
	Shader();
	~Shader();

	void Compile(GLint shaderProgram, const char* fileName, ShaderType type);
	GLint GetShaderProgram();
	GLuint GetShaderID();

private:
	int _ReadFile(const char* filename, std::string* shaderSource);
	void _AddShader(GLuint shaderProgram, const char* pShaderText, const char* fileName, GLenum ShaderType);

	GLuint _shaderID;
	GLint _shaderProgram;
};



