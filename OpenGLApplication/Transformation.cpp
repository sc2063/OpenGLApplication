#include "Transformation.h"

Transformation::Transformation()
	:trans(1.0)
{

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
void Transformation::Trans_UnUse()
{
	trans = glm::mat4(1.0f);
}
Transformation::~Transformation()
{

}