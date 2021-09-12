#pragma once
#include "Render.h"
#include <iostream>

class Texture
{
private:
	unsigned int ID_texture;
	std::string FilePath;
	unsigned char* locationBuffer;
	int Width, Height, Channels;
public:
	Texture(const std::string& path);
	~Texture();
	void Bind(unsigned int slot=0) const;
	void UnBind() const;

	inline int GetWidth()const { return Width; }
	inline int GetHeight()const { return Height; }

};

