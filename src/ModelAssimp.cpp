#include "ModelAssimp.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
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

vertices.clear();
indices.clear();

for (unsigned int i = 0; i < meshCount; i++) {
    aiMesh* mesh = scene->mMeshes[i];

        for (unsigned int j = 0; j < mesh->mNumVertices; j++) {
                aiVector3D vertex = mesh->mVertices[j];

                if (mesh ->HasPositions()) {
                    vertex = mesh->mVertices[j]; 
                    vertices.push_back(vertex.x);
                    vertices.push_back(vertex.y);
                    vertices.push_back(vertex.z);
                } 
                
                if (mesh->HasTextureCoords(0)) {
                         aiVector3D texCoord = mesh->mTextureCoords[0][j];
                          vertices.push_back(texCoord.x);
                         vertices.push_back(texCoord.y);
                } 

                if (mesh->HasNormals()) {
                         aiVector3D normal = mesh->mNormals[j];
                         vertices.push_back(normal.x);
                         vertices.push_back(normal.y);
                         vertices.push_back(normal.z);
                } 
            } 
         
        if (mesh->HasFaces()) {
            for (unsigned int j = 0; j < mesh->mNumFaces; j++) {
            aiFace face = mesh->mFaces[j];
            for (unsigned int k = 0; k < face.mNumIndices; k++) {
                indices.push_back(face.mIndices[k]);
            }
        }
    }
}
}

 vector <float> ModelAssimp::getVertices() {
    return vertices;
}

 vector <unsigned int> ModelAssimp::getIndices() {
    return indices;
}