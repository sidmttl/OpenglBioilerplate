#include "cube.h"

#include <glad/glad.h>

void Cube::loadModel(std::string const& path) {
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(
        path, aiProcess_Triangulate | aiProcess_FlipUVs |
                  aiProcess_CalcTangentSpace | aiProcess_GenNormals);
    // check for errors
    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE ||
        !scene->mRootNode)  // if  is Not Zero
    {
        std::cout << "ERROR::ASSIMP:: " << importer.GetErrorString()
                  << std::endl;
        return;
    }

    countVertex(scene->mRootNode, scene);
    p.resize(numVertices * 3);
    n.resize(numVertices * 3);
    el.resize(numFaces * 3);
    processNode(scene->mRootNode, scene);
}

void Cube::countVertex(aiNode* node, const aiScene* scene) {
    for (unsigned int i = 0; i < node->mNumMeshes; i++) {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        numVertices += mesh->mNumVertices;
        numFaces += mesh->mNumFaces;
    }

    for (unsigned int i = 0; i < node->mNumChildren; i++) {
        countVertex(node->mChildren[i], scene);
    }
}

void Cube::processNode(aiNode* node, const aiScene* scene) {
    for (unsigned int i = 0; i < node->mNumMeshes; i++) {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        processMesh(mesh, scene);
    }

    for (unsigned int i = 0; i < node->mNumChildren; i++) {
        processNode(node->mChildren[i], scene);
    }
}

void Cube::processMesh(aiMesh* mesh, const aiScene* scene) {
    for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
        // x coordiante
        p[cntr] = mesh->mVertices[i].x;
        n[cntr] = mesh->mNormals[i].x;
        cntr++;
        // y coordinate
        p[cntr] = mesh->mVertices[i].y;
        n[cntr] = mesh->mNormals[i].y;
        cntr++;
        // z coordinate
        p[cntr] = mesh->mVertices[i].z;
        n[cntr] = mesh->mNormals[i].z;
        cntr++;
    }

    for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
        aiFace face = mesh->mFaces[i];

        for (unsigned int j = 0; j < face.mNumIndices; j++) {
            el[cntr2] = face.mIndices[j];
            cntr2++;
        }
    }
}

Cube::Cube(std::string const& path) {
    loadModel(path);
    initBuffers(&el, &p, &n, nullptr, nullptr);
}
