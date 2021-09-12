#include"Render.h"
#include<iostream>
using namespace std;

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
void Render::Draw(const VertexArray& vao, const IndexBuffer& ibo, const Shader& shader)
{
	shader.Bind();
	vao.Bind();
	ibo.Bind();
	glDrawElements(GL_TRIANGLES, ibo.GetCount(), GL_UNSIGNED_INT
		, nullptr);
}