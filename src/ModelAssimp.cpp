#include "ModelAssimp.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <iostream>
#include <vector>

using namespace std;

void ModelAssimp :: LoadModel(const char* modelPath){

Assimp::Importer importer;

const aiScene* scene = importer.ReadFile(modelPath, aiProcess_Triangulate | aiProcess_FlipUVs);
if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
    cout << "ERROR::ASSIMP::" << importer.GetErrorString() << endl;
    return;
}

meshCount = scene->mNumMeshes;

for (unsigned int i = 0; i < meshCount; i++) {
    aiMesh* mesh = scene->mMeshes[i];

    if (mesh->HasPositions()) {
        for (unsigned int j = 0; j < mesh->mNumVertices; j++) {
            aiVector3D vertex = mesh->mVertices[j];
            vertices.push_back(vertex.x);
            vertices.push_back(vertex.y);
            vertices.push_back(vertex.z);
        }
    } else {
        cout << "Mesh does not have positions" << endl;
    }

    if (mesh->HasFaces()) {
        for (unsigned int j = 0; j < mesh->mNumFaces; j++) {
            aiFace face = mesh->mFaces[j];
            for (unsigned int k = 0; k < face.mNumIndices; k++) {
                indices.push_back(face.mIndices[k]);
            }
        }
    } else{
        cout << "Mesh does not have faces" << endl;
    }

    if (mesh->HasNormals()) {
        for (unsigned int j = 0; j < mesh->mNumVertices; j++) {
            aiVector3D normal = mesh->mNormals[j];
            vertices.push_back(normal.x);
            vertices.push_back(normal.y);
            vertices.push_back(normal.z);
        }
    } else {
        cout << "Mesh does not have normals" << endl;
    }

    }

    cout << vertices.size() << " vertices loaded" << endl;
    cout << indices.size() << " indices loaded" << endl;
    cout << meshCount << " meshes loaded" << endl;

}

 vector <float> ModelAssimp::getVertices() {
    return vertices;
}

 vector <unsigned int> ModelAssimp::getIndices() {
    return indices;
}