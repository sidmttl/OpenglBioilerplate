#pragma once
#include "trianglemesh.h"
#include<glad/glad.h>
#include<assimp/Importer.hpp>
#include<assimp/scene.h>
#include<assimp/postprocess.h>
#include<iostream>

class Cube : public TriangleMesh 
{
public:
	Cube(std::string const& path);

	void loadModel(std::string const& path);
	void processNode(aiNode* node, const aiScene* scene);
	void countVertex(aiNode* node, const aiScene* scene);
	void processMesh(aiMesh* mesh, const aiScene* scene);

private:
	int numVertices = 0;
	int numFaces = 0;
	int cntr = 0;
	int cntr2 = 0;

	std::vector<GLfloat> p;
	std::vector<GLfloat> n;
	std::vector<GLuint> el;
};