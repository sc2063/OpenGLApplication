#include "VertexArray.h"
#include "Render.h"

VertexArray::VertexArray()
{
	glGenVertexArrays(1, &ID);
}

VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &ID);
}

void VertexArray::Bind() const
{
	glBindVertexArray(ID);
}

void VertexArray::UnBind() const
{
	glBindVertexArray(0);
}

void VertexArray::AddBuffer(const VertexBuffer& vbo, const VertexBufferLayout& layout)
{
	const auto& elements = layout.GetElement();
	unsigned int offset = 0;
	for (unsigned int i = 0; i < elements.size(); i++)
	{
		const auto& element = elements[i];
		glEnableVertexAttribArray(i);
		glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.GetStride(), (const void*)offset);
		offset += element.count*VertexBufferElement::GetSizeofType(element.type);
	}
}
