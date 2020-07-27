/*
 * mesh.cpp
 *
 *  Created on: Jul 23, 2020
 *      Author: 123
 */

#include "ogllib/mesh.h"
#include <GL/glew.h>
#include <cstddef>

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<Texture> textures, std::vector<unsigned int> indices)
{
	mVertices = vertices;
	mTextures = textures;
	mIndices = indices;

	setupMesh();
}

void Mesh::setupMesh()
{
	glGenVertexArrays(1, &mVao);
	glGenBuffers(1, &mVbo);
	glGenBuffers(1, &mIbo);

	glBindVertexArray(mVao);

	glBindBuffer(GL_ARRAY_BUFFER, mVbo);
	glBufferData(GL_ARRAY_BUFFER, mVertices.size() * sizeof(Vertex), &mVertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIbo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, mIndices.size() * sizeof(unsigned int), &mIndices[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(Vertex, normal));

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(Vertex, texCoord));

	glBindVertexArray(0);
}

void Mesh::draw(Shader& shader)
{
	unsigned int diffuseNr = 1;
	unsigned int specularNr = 1;
	std::string number;
	std::string name;
	for (unsigned int i=0; i<mTextures.size(); i++)
	{
		mTextures[i].bind(i);
		if (mTextures[i].getType() == Texture::DIFFUSE)
		{
			number = std::to_string(diffuseNr++);
			name = "diffuse";
		}
		else if (mTextures[i].getType() == Texture::SPECULAR)
		{
			number = std::to_string(specularNr++);
			name = "specular";
		}
		shader.setUniform1i("material." + name + number, i);
	}
	glBindVertexArray(mVao);
	glDrawElements(GL_TRIANGLES, mIndices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

std::vector<Vertex> Mesh::getVertices() const
{
	return mVertices;
}

std::vector<Texture> Mesh::getTextures() const
{
	return mTextures;
}

std::vector<unsigned int> Mesh::getIndices() const
{
	return mIndices;
}
