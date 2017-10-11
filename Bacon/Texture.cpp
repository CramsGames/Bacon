#include "stdafx.h"
#include "Texture.h"

#include <cassert>
#include <iostream>
#include <fstream>
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>


Texture::Texture (std::string fileName) {
	int numComponents;
	unsigned char* imageData = stbi_load (fileName.c_str (), &_width, &_height, &numComponents, 0);

	if (imageData == NULL) {
		std::cerr << "Texture loading failed for texture: " << fileName << std::endl;
		std::cerr << stbi_failure_reason () << std::endl;
	}

	glGenTextures (1, &_texture);
	glBindTexture (GL_TEXTURE_2D, _texture);

	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameterf (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameterf (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D (GL_TEXTURE_2D, 0, GL_RGBA, _width, _height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);
	glGenerateMipmap (GL_TEXTURE_2D);

	stbi_image_free (imageData);
}

Texture::~Texture () {
	glDeleteTextures (0, &_texture);
}

void Texture::Bind (unsigned int unit) {
	assert (unit >= 0 && unit <= 31);

	glActiveTexture (GL_TEXTURE0 + unit);
	glBindTexture (GL_TEXTURE_2D, _texture);
}

int Texture::Width () {
	return _width;
}

int Texture::Height () {
	return _height;
}