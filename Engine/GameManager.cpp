#include <iostream>
#include <fstream>
#include <string>

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtx\transform.hpp>

#include "GameManager.h"
#include "Error.h"
#include "Voxel.h"


GameManager::GameManager() :
	_windowDimensions(1280, 720),
	_windowCenter(_windowDimensions.x / 2, _windowDimensions.y / 2)
{
	_Init();
}

GameManager::~GameManager()
{
}

void GameManager::_Init()
{
	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		Error::PrintError(SDL_GetError());
	}

	_window = SDL_CreateWindow("Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _windowDimensions.x, _windowDimensions.y, SDL_WINDOW_OPENGL);
	SDL_GL_CreateContext(_window);


	//Initialize OpenGL
	if (glewInit() != GLEW_OK)
	{
		Error::PrintError("Failed to initialize GLEW");
	}
	glClearColor(0.390625f, 0.546875f, 0.925781f, 1.0f); //Cornflower blue
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);


	//Additional Initialization
	SDL_WarpMouseInWindow(_window, GameManager::_windowCenter.x, GameManager::_windowCenter.y);
	_CompileShaders();
	
	

	//Start Main Loop!
	MainLoop();
}

void GameManager::_CompileShaders()
{
	_shaderProgram = glCreateProgram();

	_vertexShader = new Shader();
	_vertexShader->Compile(_shaderProgram, "vertex.shader", ShaderType::VERTEX_SHADER);

	_fragmentShader = new Shader();
	_fragmentShader->Compile(_shaderProgram, "fragment.shader", ShaderType::FRAGMENT_SHADER);

	glLinkProgram(_shaderProgram);

	glDetachShader(_shaderProgram, _vertexShader->GetShaderID());
	glDetachShader(_shaderProgram, _fragmentShader->GetShaderID());

	glUseProgram(_shaderProgram);
	delete _vertexShader;
	delete _fragmentShader;

	glDeleteProgram(_shaderProgram);

	/*const char* pFSFileName = "fragment.shader";

	_shaderProgram = glCreateProgram();
	std::string vs, fs;

	if (_ReadFile(pVSFileName, &vs) != 0)
	{
		printf("Error reading %s", pVSFileName);
	}

	if (_ReadFile(pFSFileName, &fs) != 0)
	{
		printf("Error reading %s", pFSFileName);
	}

	_AddShader(_shaderProgram, vs.c_str(), pVSFileName, GL_VERTEX_SHADER, _vertexShaderID);
	_AddShader(_shaderProgram, fs.c_str(), pFSFileName, GL_FRAGMENT_SHADER, _fragmentShaderID);

	glLinkProgram(_shaderProgram);

	glDetachShader(_shaderProgram, _vertexShaderID);
	glDetachShader(_shaderProgram, _fragmentShaderID);
	glDeleteShader(_vertexShaderID);
	glDeleteShader(_fragmentShaderID);

	glUseProgram(_shaderProgram);*/
}

void GameManager::_PollEvents()
{
	SDL_Event e;
	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_KEYDOWN)
		{
			if (e.key.keysym.sym == SDLK_ESCAPE)
			{
				_quit = true;
			}
		}

		if (e.type == SDL_QUIT)
		{
			_quit = true;
		}

		if (e.type == SDL_MOUSEMOTION)
		{
			int x = 0, y = 0;
			SDL_GetMouseState(&x, &y);
			_camera.MouseUpdate(glm::vec2(((float)x), ((float)y)), GameManager::_windowCenter);
			printf("\nMouseX:%i,MouseY:%i", x, y);
			SDL_WarpMouseInWindow(_window, GameManager::_windowCenter.x, GameManager::_windowCenter.y);

		}
	}
}


void GameManager::_HandleKeyboardInput()
{
	const Uint8* code = SDL_GetKeyboardState(NULL);
	if (code[SDL_SCANCODE_W]) _camera.isW = true;
	if (code[SDL_SCANCODE_A]) _camera.isA = true;
	if (code[SDL_SCANCODE_S]) _camera.isS = true;
	if (code[SDL_SCANCODE_D]) _camera.isD = true;
	if (code[SDL_SCANCODE_E]) _camera.isE = true;
	if (code[SDL_SCANCODE_Q]) _camera.isQ = true;
	_camera.KeyboardUpdate();
}

void GameManager::_Draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	//Generate a Cube
	glm::vec3 verts[] =
	{
		//front
		glm::vec3(-0.5f, -0.5f, +0.5f), glm::vec3(1.0f, 0.0f, 0.0f),
		glm::vec3(+0.5f, -0.5f, +0.5f), glm::vec3(1.0f, 0.0f, 0.0f),
		glm::vec3(+0.5f, +0.5f, +0.5f), glm::vec3(1.0f, 0.0f, 0.0f),
		glm::vec3(-0.5f, +0.5f, +0.5f), glm::vec3(1.0f, 0.0f, 0.0f),
		//back
		glm::vec3(+0.5f, -0.5f, -0.5f), glm::vec3(1.0f, 0.0f, 0.0f),
		glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(1.0f, 0.0f, 0.0f),
		glm::vec3(-0.5f, +0.5f, -0.5f), glm::vec3(1.0f, 0.0f, 0.0f),
		glm::vec3(+0.5f, +0.5f, -0.5f), glm::vec3(1.0f, 0.0f, 0.0f),
		//left
		glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.0f, 1.0f, 0.0f),
		glm::vec3(-0.5f, -0.5f, +0.5f), glm::vec3(0.0f, 1.0f, 0.0f),
		glm::vec3(-0.5f, +0.5f, +0.5f), glm::vec3(0.0f, 1.0f, 0.0f),
		glm::vec3(-0.5f, +0.5f, -0.5f), glm::vec3(0.0f, 1.0f, 0.0f),
		////right
		glm::vec3(+0.5f, -0.5f, +0.5f), glm::vec3(0.0f, 1.0f, 0.0f),
		glm::vec3(+0.5f, -0.5f, -0.5f), glm::vec3(0.0f, 1.0f, 0.0f),
		glm::vec3(+0.5f, +0.5f, -0.5f), glm::vec3(0.0f, 1.0f, 0.0f),
		glm::vec3(+0.5f, +0.5f, +0.5f), glm::vec3(0.0f, 1.0f, 0.0f),
		////top
		glm::vec3(-0.5f, +0.5f, +0.5f), glm::vec3(0.0f, 0.0f, 1.0f),
		glm::vec3(+0.5f, +0.5f, +0.5f), glm::vec3(0.0f, 0.0f, 1.0f),
		glm::vec3(+0.5f, +0.5f, -0.5f), glm::vec3(0.0f, 0.0f, 1.0f),
		glm::vec3(-0.5f, +0.5f, -0.5f), glm::vec3(0.0f, 0.0f, 1.0f),
		////bottom
		glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.0f, 0.0f, 1.0f),
		glm::vec3(+0.5f, -0.5f, -0.5f), glm::vec3(0.0f, 0.0f, 1.0f),
		glm::vec3(+0.5f, -0.5f, +0.5f), glm::vec3(0.0f, 0.0f, 1.0f),
		glm::vec3(-0.5f, -0.5f, +0.5f), glm::vec3(0.0f, 0.0f, 1.0f),
		
		
	};

	GLuint indices[] =
	{
		0, 1, 2, 2, 3, 0, //front
		4, 5, 6, 6, 7, 4, //back
		8, 9, 10, 10, 11, 8, //left
		12, 13, 14, 14, 15, 12, //right
		16, 17, 18, 18, 19, 16, //top
		20, 21, 22, 22, 23, 20 //bottom
	};

	glGenBuffers(1, &_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, _VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GL_FLOAT) * 6, 0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(GL_FLOAT) * 6, (void*)(sizeof(GL_FLOAT) * 3));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);


	glGenBuffers(1, &_IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


	GLint fullTransformMatrixUniformLocation = glGetUniformLocation(_shaderProgram, "fullTransformMatrix");
	glm::mat4 fullTransformMatrix;
	glm::mat4 projectionMatrix = glm::perspective(glm::radians(60.0f), ((float)1280) / 720, 0.1f, 10.0f);
	glm::mat4 viewMatrix = _camera.GetWorldToViewMatrix();

	glm::mat4 modelMatrix = glm::translate(glm::vec3(0.0f, 0.0f, 0.0f));// *glm::rotate(glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	fullTransformMatrix = projectionMatrix * viewMatrix * modelMatrix;
	glUniformMatrix4fv(fullTransformMatrixUniformLocation, 1, GL_FALSE, &fullTransformMatrix[0][0]);

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	SDL_GL_SwapWindow(_window);
}

void GameManager::MainLoop()
{
	while (!_quit)
	{
		_PollEvents();
		_HandleKeyboardInput();
		_Draw();
	}
}
