#include "Model.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;


void Model::loadModel(const char* path){

   
   Position pos;
   Color col;
   Normal norm;
   TexCoord tex;
   Face f;

   //Open the model file
    string line;
    string name;
    ifstream file(path);
    if (!file.is_open()) {
        cout << "Error opening file: " << path << endl;
        return;
    } else{
        cout << "File opened successfully: " << path << endl;
    }

    while (getline(file,line)){

        istringstream iss(line);
        string prefix;

        // Read the first word of the line
        iss >> prefix;

        // Check the name of the object
        if (prefix == "o"){
            iss >> name;
            //debug
            cout << "Object name: " << name << endl;
        }
        
        // Check the position of the object
        if (prefix == "v"){
            iss >> pos.x >> pos.y >> pos.z;
            //debug
            cout << "Position: " << pos.x << " " << pos.y << " " << pos.z << endl;
            position.push_back(pos);

        }

        // Check the vertex normal of the object
        if (prefix == "vn"){
            iss >> norm.nx >> norm.ny >> norm.nz;
            //debug
            cout << "Normal: " << norm.nx << " " << norm.ny << " " << norm.nz << endl;
            normal.push_back(norm);
        }

        // Check the texture coordinates of the object
        if (prefix == "vt"){
            iss >> tex.u >> tex.v;\
            //debug
            cout << "Texture coordinates: " << tex.u << " " << tex.v << endl;
            texCoord.push_back(tex);
        }

        if (prefix == "f"){
             vector < unsigned int> vertexIndex, normalIndex, texCoordIndex;
             unsigned int vIndex, nIndex, tIndex;
            char slash;


            // Read the through the indexes of the vertices
            for (int i = 0; i < 4; i++)
            {
                iss >> vIndex >> slash >> tIndex >> slash >> nIndex;
                //debug
                cout << vIndex << "/" << tIndex << "/" << nIndex << endl;
                vertexIndex.push_back(vIndex);
                texCoordIndex.push_back(tIndex);
                normalIndex.push_back(nIndex);
            }

            // Read the indexes of the vertices
            for (int i = 0; i < 4; i++)
            {
                f.vertexIndex = vertexIndex[i];
                f.normalIndex = normalIndex[i];
                f.texCoordIndex = texCoordIndex[i];
                face.push_back(f);
            }
            
        }
    }

}

