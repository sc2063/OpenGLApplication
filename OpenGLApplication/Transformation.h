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

public:
	Transformation();
	~Transformation();
	glm::mat4 Trans(const std::string type,const float value, const glm::vec3& vector);
	glm::mat4 Trans(const std::string type, const glm::vec3& vector);
	void Trans_UnUse();
};

