#include <iostream>
#include <fstream>

#include "Shader.h"


Shader::Shader()
{
	
}


Shader::~Shader()
{
}

int Shader::_ReadFile(const char* filename, std::string* shaderSource)
{

	std::ifstream fileStream(filename, std::ios::in);

	if (!fileStream.is_open())
	{
		std::cerr << "Could not read file " << filename << ". File does not exist." << std::endl;
		return -1;
	}

	std::string line = "";
	while (!fileStream.eof())
	{
		std::getline(fileStream, line);
		(*shaderSource).append(line + "\n");
	}

	fileStream.close();
	return 0;

}

void Shader::_AddShader(GLuint shaderProgram, const char* pShaderText, const char* fileName, GLenum ShaderType)
{
	_shaderID = glCreateShader(ShaderType);

	const GLint length = strlen(pShaderText);
	GLint success;
	glShaderSource(_shaderID, 1, &pShaderText, &length);
	glCompileShader(_shaderID);
	glGetShaderiv(_shaderID, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		GLchar InfoLog[1024];
		glGetShaderInfoLog(_shaderID, 1024, NULL, InfoLog);
		printf("Error compiling shader file name %s:\n%s\n", fileName, InfoLog);
		std::cin.get();
		exit(1);
	}
	glAttachShader(shaderProgram, _shaderID);
}

void Shader::Compile(GLint shaderProgram, const char* fileName, ShaderType type)
{
	_shaderProgram = shaderProgram;
	//memcpy(&_shaderProgram, &shaderProgram, sizeof(shaderProgram));
	std::string shaderSource;

	if (_ReadFile(fileName, &shaderSource) != 0)
	{
		printf("Error reading %s", fileName);
	}

	if (type == ShaderType::VERTEX_SHADER)
		_AddShader(shaderProgram, shaderSource.c_str(), fileName, GL_VERTEX_SHADER);
	else if (type == ShaderType::FRAGMENT_SHADER)
		_AddShader(shaderProgram, shaderSource.c_str(), fileName, GL_FRAGMENT_SHADER);
	
}

GLint Shader::GetShaderProgram()
{
	return _shaderProgram;
}

GLuint Shader::GetShaderID()
{
	return _shaderID;
}