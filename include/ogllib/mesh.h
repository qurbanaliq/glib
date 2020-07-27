/*
 * mesh.h
 *
 *  Created on: Jul 23, 2020
 *      Author: 123
 */

#pragma once
#include <glm/glm.hpp>
#include <string>
#include <vector>
#include "ogllib/shader.h"
#include "ogllib/texture.h"

/*
 * stores the vertex data
 */
struct Vertex
{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 texCoord;
};

/*
 * stores the mesh data
 */
class Mesh
{
private:
	std::vector<Vertex> mVertices;
	std::vector<Texture> mTextures;
	std::vector<unsigned int> mIndices;
	unsigned int mVao, mVbo, mIbo;

	void setupMesh();

public:
	/*
	 * creates new mesh object with given vertices, textures and indices
	 */
	Mesh(std::vector<Vertex> vertices, std::vector<Texture> textures, std::vector<unsigned int> indices);

	/*
	 * draws/renders the mesh
	 */
	void draw(Shader& shader);

	/*
	 * returns all the vertices
	 */
	std::vector<Vertex> getVertices() const;

	/*
	 * return all the textures
	 */
	std::vector<Texture> getTextures() const;

	/*
	 * return all the indices
	 */
	std::vector<unsigned int> getIndices() const;
};
