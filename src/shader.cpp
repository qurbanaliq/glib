#define GLEW_STATIC
#include <GL/glew.h>
#include "shader.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath)
{
	std::string vertexSource = parseShaderSource(vertexPath);
	std::string fragmentSource = parseShaderSource(fragmentPath);
	unsigned int vShader = compileShader(GL_VERTEX_SHADER, vertexSource);
	unsigned int fShader = compileShader(GL_FRAGMENT_SHADER, fragmentSource);
	m_ID = createShader(vShader, fShader);
}

Shader::~Shader()
{
	glDeleteProgram(m_ID);
}

void Shader::use()
{
	glUseProgram(m_ID);
}

std::string Shader::parseShaderSource(const std::string &filePath)
{
	std::ifstream shaderFile;
	std::stringstream shaderStream;
	// enable exceptions
	shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try
	{
		shaderFile.open(filePath);
		shaderStream << shaderFile.rdbuf();
		shaderFile.close();
	}
	catch(std::ifstream::failure e)
	{
		std::cout << "Error: could not read shader source: " << e.what() <<
				std::endl;
		return "";
	}
	return shaderStream.str();
}

void Shader::checkLinkErrors(unsigned int program)
{
	int success;
	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success)
	{
		int length;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);
		char* info = new char[length];
		glGetProgramInfoLog(program, sizeof(char) * length, NULL, info);
		std::cout << info << std::endl;
		delete[] info;
	}
}

unsigned int Shader::createShader(unsigned int vShader, unsigned int fShader)
{
	unsigned int id = glCreateProgram();
	glAttachShader(id, vShader);
	glAttachShader(id, fShader);
	glLinkProgram(id);
	checkLinkErrors(id);
	glValidateProgram(id);
	glDeleteShader(vShader);
	glDeleteShader(fShader);
	return id;
}

void Shader::checkCompileErrors(unsigned int shader)
{
	int success;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		int length;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
		char* info = new char[length];
		glGetShaderInfoLog(shader, sizeof(char) * length, NULL, info);
		std::cout << info << std::endl;
		delete[] info;
	}
}

unsigned int Shader::compileShader(unsigned int type,
		const std::string &source)
{
	unsigned int shader = glCreateShader(type);
	const char* src = source.c_str();
	glShaderSource(shader, 1, &src, nullptr);
	glCompileShader(shader);
	checkCompileErrors(shader);
	return shader;
}

unsigned int Shader::getUniformLocation(const std::string &name)
{
	if (m_uniformCache.find(name) == m_uniformCache.end())
		m_uniformCache[name] = glGetUniformLocation(m_ID, name.c_str());
	return m_uniformCache[name];
}

void Shader::setUniform4f(const std::string &name, float v1, float v2, float v3,
		float v4)
{
	glUniform4f(getUniformLocation(name), v1, v2, v3, v4);
}

void Shader::setUniform3f(const std::string &name, float v1, float v2,
		float v3)
{
	glUniform3f(getUniformLocation(name), v1, v2, v3);
}

void Shader::setUniform2f(const std::string &name, float v1, float v2)
{
	glUniform2f(getUniformLocation(name), v1, v2);
}

void Shader::setUniform1f(const std::string &name, float v)
{
	glUniform1f(getUniformLocation(name), v);
}
