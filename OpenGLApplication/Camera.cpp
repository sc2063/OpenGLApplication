#include "Camera.h"

void Camera::CameraVectors()
{
	glm::vec3 direction;
	direction.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
	direction.y = sin(glm::radians(Pitch));
	direction.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
	C_Front = glm::normalize(direction);
	C_Right = glm::normalize(glm::cross(C_Front, WordUP));
	C_Up = glm::normalize((glm::cross(C_Right, C_Front)));
}

Camera::Camera(const glm::vec3 Pos)
	:Sensitivity(0.1f),SPEED(8.0f),C_Front(0),C_Up(glm::vec3(0.0,1.0,0.0)),Yaw(-90.0f),Pitch(0.0f),Roll(0.0f),CameraSpeed(0)
{
	WordUP = C_Up;
	this->C_Pos = Pos;
	CameraVectors();
}

glm::mat4 Camera::GetViewMaritx()
{
	glm::mat4 view = glm::lookAt(C_Pos, C_Pos + C_Front, C_Up);
	view = glm::rotate(view, glm::radians(Roll), C_Pos);
	return view;
}

void Camera::KeyMove(KeyWord key, float deltaTime)
{
	CameraSpeed = SPEED * deltaTime;
	switch (key)
	{
	case KeyWord::LEFT:
		CameraVectors();
		C_Pos -= C_Right * CameraSpeed;
		break;
	case KeyWord::RIGHT:
		CameraVectors();
		C_Pos += C_Right * CameraSpeed;
		break;
	}
}
void Camera::Mouse_Movement(float xoffset, float yoffset, float zoffset)
{
	xoffset *= Sensitivity;
	yoffset *= Sensitivity;
	zoffset *= Sensitivity;


	Yaw += xoffset;
	Pitch += yoffset;
	Roll += zoffset;
	CameraVectors();
}
void Camera::Mouse_Movement(float yoffset)
{
	if (yoffset > 0)
	{
		C_Pos += CameraSpeed * 10 * C_Front;
	}
	if (yoffset < 0)
	{
		C_Pos -= CameraSpeed * 10 * C_Front;
	}
}
void Camera::Mouse_Movement(const KeyWord key, float deltaTime)
{
	CameraSpeed = SPEED * deltaTime;
	switch (key)
	{
	case KeyWord::LEFT:
		C_Pos -= C_Right*CameraSpeed;
		break;
	case KeyWord::RIGHT:
		C_Pos += C_Right*CameraSpeed;
		break;
	case KeyWord::UP:
		C_Pos += C_Up * CameraSpeed;
		break;
	case KeyWord::DOWN:
		C_Pos -= C_Up * CameraSpeed;
		break;
	}
}