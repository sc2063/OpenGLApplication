#pragma once
#include"VertexBuffer.h"
#include"VertexBufferLayout.h"
class VertexArray
{
private:
	unsigned int ID;
public:
	VertexArray();
	~VertexArray();
	void Bind() const;
	void UnBind() const;
	void AddBuffer(const VertexBuffer& vbo, const VertexBufferLayout& layout);
};

