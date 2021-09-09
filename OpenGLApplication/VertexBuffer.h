#pragma once
class VertexBuffer
{
private:
	unsigned int ID;
	const void* Data;
	unsigned int Size;
public:
	VertexBuffer(const void* data, unsigned int size);
	~VertexBuffer();
	void Bind() const;
	void UnBind() const;
};

