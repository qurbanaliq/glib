/*
 * model.h
 *
 *  Created on: Jul 25, 2020
 *      Author: 123
 */
#pragma once
#include "ogllib/shader.h"
#include "ogllib/mesh.h"
#include "ogllib/texture.h"
#include <vector>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

class Model
{
public:
	/*
	* Create a model given a model file path
	*/
	Model(const std::string& path);

	/*
	* Draws the model on the opengl screen
	*/
	void draw(Shader& shader);

private:
	std::vector<Mesh> mMeshes;
	std::string mDirectory;
	std::vector<Texture> mLoadedTextures;
	std::string mPath;

	void loadModel(const std::string& path);
	void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);
	std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, Texture::TEXTURE_TYPES tType);
};
