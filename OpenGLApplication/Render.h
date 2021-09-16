#pragma once
#include<GL/glew.h>
#include "Shader.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "glm/glm/glm.hpp"
#include "glm/glm/gtc/matrix_transform.hpp"
#include "glm/glm/gtc/type_ptr.hpp"

#define ASSERT(x) if(!(x))__debugbreak();
#define GL_Check(x) GLClearError();\
		x;\
		ASSERT(GLLogCall(#x,__FILE__,__LINE__))
void GLClearError();
bool GLLogCall(const char* function, const char* file, int line);

class VertexArray;
class IndexBuffer;
class Shader;

class Render
{
private:
	unsigned int cube_Count;
	inline unsigned int GetCount(unsigned int num) const
	{
		return cube_Count;
	}
public:
	void Clear();
	void Draw(const VertexArray& vao, const IndexBuffer& ibo, Shader& shader,const glm::vec3 *cubePositions);
	Render(const unsigned int num);
};

