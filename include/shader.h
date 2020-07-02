/*
 * shader.h
 *
 *  Created on: Jul 1, 2020
 *      Author: 123
 */

#pragma once

#include <string>

class Shader
{
private:
	unsigned int m_ID;
	// TODO: uniformCache

	std::string parseShaderSource(const std::string& filePath);
	unsigned int createShader(unsigned int vShader, unsigned int fShader);
	unsigned int compileShader(unsigned int type, const std::string& source);
	unsigned int getUniformLocation(const std::string& name);

public:
	Shader(const std::string& vertexPath, const std::string& fragmentPath);
	~Shader();

	void use();
	void setUniform4f(const std::string& name, float v1, float v2,
			float v3, float v4);
	void setUniform3f(const std::string& name, float v1, float v2, float v3);
	void setUniform2f(const std::string& name, float v1, float v2);
	void setUniform1f(const std::string& name, float v);
};
