#pragma once

#include <GL\glew.h>
#include <SDL.h>

#include "Camera.h"


class GameManager
{
public:
	GameManager();
	~GameManager();

	void MainLoop();

private:
	void _AddShader(GLuint shaderProgram, const char* pShaderText, const char* fileName, GLenum ShaderType, GLuint &shaderID);
	int _ReadFile(const char* filename, std::string* shaderSource);
	void _CompileShaders();
	void _Start();
	void _PollEvents();
	void _Draw();
	void _HandleKeyboardInput();

	glm::vec2 _windowCenter;
	bool _quit = false;
	SDL_Window* _window;
	GLuint _VBO, _IBO;
	GLint _shaderProgram;
	GLuint _vertexShaderID;
	GLuint _fragmentShaderID;
	Camera _camera;

};

