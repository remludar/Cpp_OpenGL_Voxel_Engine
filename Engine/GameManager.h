#pragma once

#include <GL\glew.h>
#include <SDL.h>

#include "Camera.h"
#include "Shader.h"


class GameManager
{
public:
	GameManager();
	~GameManager();

	void MainLoop();

private:
	void _Init();
	void _CompileShaders();
	void _PollEvents();
	void _Draw();
	void _HandleKeyboardInput();

	glm::vec2 _windowDimensions;
	glm::vec2 _windowCenter;
	bool _quit = false;
	SDL_Window* _window;
	GLuint _VBO, _IBO;
	GLint _shaderProgram;
	GLuint _vertexShaderID;
	GLuint _fragmentShaderID;
	Camera _camera;
	Shader *_vertexShader;
	Shader *_fragmentShader;
};

