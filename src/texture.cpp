/*
 * texture.cpp
 *
 *  Created on: Jul 8, 2020
 *      Author: 123
 */
#include "ogllib/texture.h"
#include <iostream>


Texture::Texture(const std::string& path, TEXTURE_TYPES typ) : mType(typ), mPath(path)
{
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load(path.c_str(), &m_width, &m_height, &m_channels, 0);

	glGenTextures(1, &m_ID);
	glBindTexture(GL_TEXTURE_2D, m_ID);

	//set the wrapping options
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// set the minifying and magnifying options
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	int channels = GL_RGB;
	if (m_channels == 4) channels = GL_RGBA;

	glTexImage2D(GL_TEXTURE_2D, 0, channels, m_width, m_height, 0, channels, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);

	// unbind the texture after setting all the options
	// and bind it later when required
	unbind();

	// free the image buffer
	stbi_image_free(data);
}

Texture::~Texture()
{

}

void Texture::bind(unsigned int unit = 0)
{
	glActiveTexture(GL_TEXTURE0 + unit);
	glBindTexture(GL_TEXTURE_2D, m_ID);
}

void Texture::unbind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

Texture::TEXTURE_TYPES Texture::getType() const
{
	return mType;
}

std::string Texture::getPath() const
{
	return mPath;
}