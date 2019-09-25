#pragma once
#include "stb_image.h"

#include <iostream>

class TextureResource {
private:
	int width, height, nrChannels;
	unsigned int texture;
	unsigned char* data;
public:
	TextureResource();
	~TextureResource();

	void loadTextureFromFile(const char* fileName);
	void generateTexture();

	void bindTexture();
};

inline TextureResource::TextureResource() {
	width = 0;
	height = 0;
	nrChannels = 0;
	texture = 0;
}

inline TextureResource::~TextureResource() {
	width = 0;
	height = 0;
	nrChannels = 0;
	texture = 0;
	delete data;
	glDeleteTextures(1, &texture);
}

inline void TextureResource::loadTextureFromFile(const char* filename) {
	//data = stbi_load(filename, &width, &height, &nrChannels, 0);
	data = stbi_load("C:\\Users\\Work\\Desktop\\container.jpg", &width, &height, &nrChannels, 0);
}

inline void TextureResource::generateTexture() {
	glGenTextures(1, &texture);

	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(data);
}

inline void TextureResource::bindTexture() {
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
}