/*
 * texture.h
 *
 *  Created on: Jul 8, 2020
 *      Author: 123
 */
#pragma once

#include <stbImage/stbImage.h>
#include <string>
#include <GL/glew.h>

class Texture
{
private:
	unsigned int m_ID;
	int m_width, m_height, m_channels;

public:
	Texture(const std::string& path);
	~Texture();
	void bind(unsigned int unit);
	void unbind();
};
