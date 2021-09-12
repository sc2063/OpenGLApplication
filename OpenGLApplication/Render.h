#pragma once
#include<GL/glew.h>
#include "Shader.h"
#include "VertexArray.h"
#include "IndexBuffer.h"

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
public:
	void Clear();
	void Draw(const VertexArray& vao,const IndexBuffer& ibo,const Shader& shader) ;
};

