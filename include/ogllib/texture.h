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
	/*
	* Create a 2D texture given a file path of the image file
	*/
	Texture(const std::string& path, TEXTURE_TYPES type);
	~Texture();
	
	/*
	* Bind this texture
	*/
	void bind(unsigned int unit);

	/*
	* Unbind this texture
	*/
	void unbind();

	/*
	* Returns the type of the texture
	*/
	TEXTURE_TYPES getType() const;

	/*
	* Returns the file path of the texture
	*/
	std::string getPath() const;

private:
	unsigned int m_ID;
	int m_width, m_height, m_channels;
	TEXTURE_TYPES mType;
	std::string mPath;
};
