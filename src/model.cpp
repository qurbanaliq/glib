/*
 * model.cpp
 *
 *  Created on: Jul 25, 2020
 *      Author: 123
 */
#include "ogllib/model.h"
#include <iostream>
#include "ogllib/mesh.h"

Model::Model(std::string& path)
{
	loadModel(path);
}

void Model::draw(Shader& shader)
{
	for (Mesh mesh: mMeshes)
		mesh.draw(shader);
}

void Model::loadModel(std::string& path)
{
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		std::cout << "Error::Assimp::"<< importer.GetErrorString() << std::endl;
		return;
	}
	mDirectory = path.substr(0, path.find_last_of("/"));
	processNode(scene->mRootNode, scene);
}

void Model::processNode(aiNode* node, const aiScene* scene)
{
	// process all the meshes for a node
	for (unsigned int i=0; i<node->mNumMeshes; i++)
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		mMeshes.push_back(processMesh(mesh, scene));
	}

	//process child nodes of a node
	for (unsigned int i=0; i<node->mNumChildren; i++)
		processNode(node->mChildren[i], scene);
}

Mesh Model::processMesh(aiMesh* mesh, const aiScene* scene)
{
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture> textures;

	for (unsigned int i=0; i<mesh->mNumVertices; i++)
	{
		Vertex vertex;
		vertex.position = glm::vec3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);
		vertex.normal = glm::vec3(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z);
		if (mesh->mTextureCoords[0])
			vertex.texCoord = glm::vec2(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y);
		else
			vertex.texCoord = glm::vec2(0.0f, 0.0f);
		vertices.push_back(vertex);
	}
	for (unsigned int i=0; i<mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		for (unsigned int j=0; j<face.mNumIndices; j++)
			indices.push_back(face.mIndices[j]);
	}
	if (mesh->mMaterialIndex >= 0)
	{
		aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
		std::vector<Texture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, Texture::DIFFUSE);
		textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
		std::vector<Texture> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, Texture::SPECULAR);
		textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
	}
	return Mesh(vertices, textures, indices);
}

std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, Texture::TEXTURE_TYPES tType)
{
	std::vector<Texture> textures;
	for (unsigned int i=0; i<mat->GetTextureCount(type); i++)
	{
		aiString str;
		mat->GetTexture(type, i, &str);
		textures.push_back(Texture(str.C_Str(), tType));
	}
	return textures;
}
