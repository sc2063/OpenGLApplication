#include "VertexBuffer.h"
#include"Render.h"
VertexBuffer::VertexBuffer(const void* data, unsigned int size)
{
	glGenBuffers(1, &ID);
	this->Data = data;
	this->Size = size;
}
void VertexBuffer::Bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, ID);
	glBufferData(GL_ARRAY_BUFFER, Size, Data, GL_STATIC_DRAW);
}
void VertexBuffer::UnBind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(1, &ID);
}