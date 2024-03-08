#include "texture.h"
#include "stb_image.h"

Texture::Texture()
{
	_textureID = 0;
	_width = 0;
	_height = 0;
	_bitDepth = 0;
}

void Texture::initialise(std::string fileLoc)
{
	unsigned char *texData = stbi_load(fileLoc.c_str(), &_width, &_height, &_bitDepth, 0);
	if (!texData)
	{
		std::cout << "Failed to find : %s\n"
				  << fileLoc;
		return;
	}

	glGenTextures(1, &_textureID);
	glBindTexture(GL_TEXTURE_2D, _textureID);

	// Set texture parameters and generate mipmaps
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// Load texture data and generate mipmaps
	if (_bitDepth == 3)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, _width, _height, 0, GL_RGB, GL_UNSIGNED_BYTE, texData);
	}
	else if (_bitDepth == 4)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _width, _height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texData);
	}
	glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0);

	stbi_image_free(texData);
}

void Texture::use()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, _textureID);
}

void Texture::clear()
{
	glDeleteTextures(1, &_textureID);
	_textureID = 0;
	_width = 0;
	_height = 0;
	_bitDepth = 0;
}

Texture::~Texture()
{
	clear();
}