#include "Transformation.h"

Transformation::Transformation(float screeneWidth, float screenHeight)
	:trans(1.0),S_Width(screeneWidth),S_Height(screenHeight),m_model(1.0f),m_projection(1.0f)
{
	normalize();
}

glm::mat4 Transformation::Trans(std::string type,const float value, const glm::vec3& vector)
{
	transform(type.begin(), type.end(), type.begin(), ::tolower);

	if (type == "rotate")
	{
		trans = glm::rotate(trans, glm::radians(value), vector);
		return trans;
	}
	std::cout<<"Transform ERROR"<<std::endl;
}
glm::mat4 Transformation::Trans(std::string type, const glm::vec3& vector)
{
	transform(type.begin(), type.end(), type.begin(), ::tolower);

	if (type == "scale")
	{
		trans = glm::scale(trans, vector);
		return trans;
	}	
	if (type == "translate")
	{ 
		trans = glm::translate(trans, vector);
		return trans;
	}
	std::cout << "Transform ERROR" << std::endl;
}
void Transformation::normalize()
{
	m_model = glm::rotate(m_model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	m_projection = glm::perspective(glm::radians(45.0f), float(S_Width) / float(S_Height), 0.1f, 100.0f);
}