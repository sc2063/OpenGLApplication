#pragma once
class IndexBuffer
{
private:
	unsigned int ID;
	unsigned int m_Count;
	const void* Data;
	unsigned int Count;
public:
	IndexBuffer(const void*data,unsigned int count);
	~IndexBuffer();
	void Bind() const;
	void UnBind() const;

	inline unsigned int GetCount() const
	{
		return m_Count;
	}
};

