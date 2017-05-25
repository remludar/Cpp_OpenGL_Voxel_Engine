#pragma once

#include <glm\glm.hpp>

class Camera
{

	glm::vec3 position;
	glm::vec3 viewDirection;
	const glm::vec3 UP;
	float mouseSpeed = 0.18f;
	float moveSpeed = 0.05f;
public:
	Camera();
	~Camera();

	void MouseUpdate(const glm::vec2& newMousePosition, const glm::vec2& windowCenter);
	void KeyboardUpdate();

	glm::mat4 GetWorldToViewMatrix() const;
	bool isW;
	bool isA;
	bool isS;
	bool isD;
	bool isE;
	bool isQ;
};

