#include "Texture.h"
#include "stb_image.h"

Texture::Texture(const std::string& path)
	:ID_texture(0),
	FilePath(path),
	locationBuffer(nullptr),
	Width(0),Height(0),Channels(0)
{
	stbi_set_flip_vertically_on_load(1);
	locationBuffer = stbi_load(path.c_str(), &Width, &Height, &Channels, 4);

	glGenTextures(1, &ID_texture);
	glBindTexture(GL_TEXTURE_2D, ID_texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	if (locationBuffer)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, Width, Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, locationBuffer);
		glGenerateMipmap(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(locationBuffer);
}

Texture::~Texture()
{
	glDeleteTextures(1, &ID_texture);
}

void Texture::Bind(unsigned int slot) const
{
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, ID_texture);
}

void Texture::UnBind() const
{
	glBindTexture(GL_TEXTURE_2D, 0);
}
