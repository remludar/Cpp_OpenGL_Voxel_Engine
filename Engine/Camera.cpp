#include <glm\gtx\transform.hpp>

#include "Camera.h"


Camera::Camera():
	position(0.0f, 2.0f, 2.0f),
	viewDirection(0.0f, -0.5f, -1.0f),
	UP(0.0f, 1.0f, 0.0f)
{
}


Camera::~Camera()
{
}


void Camera::MouseUpdate(const glm::vec2& newMousePosition, const glm::vec2& windowCenter)
{
	//glm::vec2 windowCenter(640, 360);

	glm::vec2 mouseDelta = newMousePosition - windowCenter;
	glm::vec3 yRotVector = glm::cross(viewDirection, UP);
	viewDirection = glm::mat3(
		glm::rotate(glm::radians(-mouseDelta.x) * mouseSpeed, UP) *
		glm::rotate(glm::radians(-mouseDelta.y) * mouseSpeed, yRotVector)) * viewDirection;
}

void Camera::KeyboardUpdate()
{
	if (isW)
	{
		position += viewDirection * moveSpeed;
	}

	if (isA)
	{
		position -= glm::cross(viewDirection, UP) * moveSpeed;
	}

	if (isS)
	{
		position -= viewDirection * moveSpeed;
	}

	if (isD)
	{
		position += glm::cross(viewDirection, UP) * moveSpeed;
	}

	if (isE)
	{
		position += UP * moveSpeed;
	}

	if (isQ)
	{
		position -= UP * moveSpeed;
	}

	isW = isA = isS = isD = isE = isQ = false;

}

glm::mat4 Camera::GetWorldToViewMatrix() const
{
	return glm::lookAt(position, position + viewDirection, UP);
}

