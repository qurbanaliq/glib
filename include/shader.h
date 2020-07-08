/**
 * shader.h
 *
 * Created on: Jul 1, 2020
 * Author: Qurban Ali
 *
 * Shader class is part of the ogllib, an opengl library.
 * ogllib is a library to abstract out the creation of objects
 * such as shaders, buffers, vertex arrays, etc.
 *
 * Shader class abstract out the functionality to create and use
 * vertex and fragment shaders.
 */

#pragma once

#include <string>
#include <unordered_map>
#include <glm/glm.hpp>

class Shader
{
private:
	unsigned int m_ID; // shader program id
	std::unordered_map<std::string, int> m_uniformCache; // cache uniform locations

	std::string parseShaderSource(const std::string& filePath);
	unsigned int createShader(unsigned int vShader, unsigned int fShader);
	unsigned int compileShader(unsigned int type, const std::string& source);
	unsigned int getUniformLocation(const std::string& name);
	void checkCompileErrors(unsigned int shader);
	void checkLinkErrors(unsigned int program);

public:

	/**
	 * Create a new shader from given vertex and fragment shader file paths.
	 * @param vertexPath File path for vertex shader source code
	 * @param fragmentPath File path for fragment shader source code
	 */
	Shader(const std::string& vertexPath, const std::string& fragmentPath);

	/**
	 * Destructor
	 */
	~Shader();

	/**
	 * Use this shader for future draw calls.
	 */
	void use();

	/**
	 * Set uniform with four float numbers.
	 * @param v1, v2, v3, v4 Float values to be set
	 */
	void setUniform4f(const std::string& name, float v1, float v2,
			float v3, float v4);

	/**
	 * Set uniform with three float values
	 * @param v1, v2, v3 Float values to be set
	 */
	void setUniform3f(const std::string& name, float v1, float v2, float v3);

	/**
	 * Set uniform with two float values
	 * @param v1, v2 Float values to be set
	 */
	void setUniform2f(const std::string& name, float v1, float v2);

	/**
	 * Set uniform with one float values
	 * @param v Float value to be set
	 */
	void setUniform1f(const std::string& name, float v);

	/**
	 * Set uniform with 1 int value
	 * @param v Int value to be set
	 */
	void setUniform1i(const std::string& name, int v);

	/**
	 * Set uniform with mat4 value
	 */
	void setUniformMat4fv(const std::string& name, glm::mat4& value);
};
