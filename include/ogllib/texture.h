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
public:
	enum TEXTURE_TYPES { DIFFUSE, SPECULAR };
	Texture(const std::string& path, TEXTURE_TYPES type);
	~Texture();
	void bind(unsigned int unit);
	void unbind();
	TEXTURE_TYPES getType() const;
	std::string getPath() const;

private:
	unsigned int m_ID;
	int m_width, m_height, m_channels;
	TEXTURE_TYPES mType;
	std::string mPath;
};
