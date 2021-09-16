#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <algorithm>
#include "glm/glm/glm.hpp"
#include "glm/glm/gtc/matrix_transform.hpp"
#include "glm/glm/gtc/type_ptr.hpp"



class Transformation
{
private: 
	glm::mat4 trans;
	const float S_Width;
	const float S_Height;
public:
	glm::mat4 m_model;
	glm::mat4 m_projection;

	Transformation(float screeneWidth , float screenHeight);
	glm::mat4 Trans(const std::string type,const float value, const glm::vec3& vector);
	glm::mat4 Trans(const std::string type, const glm::vec3& vector);
	void normalize();
};

