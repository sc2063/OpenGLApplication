#pragma once
#include "glm/glm/glm.hpp"
#include "glm/glm/gtc/matrix_transform.hpp"
#include "glm/glm/gtc/type_ptr.hpp"
#include <iostream>
enum class KeyWord
{
	LEFT, RIGHT, UP, DOWN
};
class Camera
{
private:
	float Yaw;
	float Pitch;
	float Roll;
	glm::vec3 C_Pos;
	glm::vec3 C_Front;
	glm::vec3 C_Right;
	glm::vec3 C_Up;
	glm::vec3 WordUP;

	const float SPEED;
	const float Sensitivity;
	float CameraSpeed;
	void CameraVectors();
public:
	Camera(const glm::vec3 Pos);
	glm::mat4 GetViewMaritx();
	void KeyMove(KeyWord key, float deltaTime);
	void Mouse_Movement(float xoffset, float yoffset, float zoffset);
	void Mouse_Movement(float yoffset);
	void Mouse_Movement(const KeyWord key, float deltaTime);
};

