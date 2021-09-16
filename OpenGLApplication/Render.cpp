#include"Render.h"
#include<iostream>
using namespace std;

Render::Render(const unsigned int num)
	:cube_Count(num){}

void GLClearError()
{
	while (glGetError() != GL_NO_ERROR);
}
bool GLLogCall(const char* function, const char* file, int line)
{
	while (GLenum error=glGetError())
	{
		std::cout << "[OpenGL Error]" << error << ":" << function << " " << file << "£º" << line << std::endl;
		return false;
	}
	return true;
}
void Render::Clear()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
void Render::Draw(const VertexArray& vao, const IndexBuffer& ibo, Shader& shader, const glm::vec3* cubePositions)
{
	shader.Bind();
	vao.Bind();
	ibo.Bind();
	for (unsigned int i = 0; i < cube_Count; i++)
	{
		// calculate the model matrix for each object and pass it to shader before drawing	
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, cubePositions[i]);
		float angle = 45 * i;
		model = glm::rotate(model, glm::radians(angle), glm::vec3(0.0, 1.0, 0.0));
		shader.SetUniformMatrix4fv("model", model);

		glDrawElements(GL_TRIANGLES, ibo.GetCount(), GL_UNSIGNED_INT
			, nullptr);
	}
	glHint(GL_POLYGON_SMOOTH, GL_NICEST);
}