#include"IndexBuffer.h"
#include"Render.h"
IndexBuffer::IndexBuffer(const void* data, unsigned int count)
	: m_Count(count)
{
	glGenBuffers(1, &ID);
	this->Data = data;
	this->Count = m_Count;
;
}
IndexBuffer::~IndexBuffer()
{
	glDeleteBuffers(1, &ID);
}
void IndexBuffer::Bind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, Count * sizeof(unsigned int), Data, GL_STATIC_DRAW);
}
void IndexBuffer::UnBind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}