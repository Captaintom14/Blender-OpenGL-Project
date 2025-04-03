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
         //   cout << "Object name: " << name << endl;
        }
        
        // Check the position of the object
        if (prefix == "v"){
            iss >> pos.x >> pos.y >> pos.z;
            //debug
         //  cout << "Position: " << pos.x << " " << pos.y << " " << pos.z << endl;
            position.push_back(pos);

        }

        // Check the vertex normal of the object
        if (prefix == "vn"){
            iss >> norm.nx >> norm.ny >> norm.nz;
            //debug
          //  cout << "Normal: " << norm.nx << " " << norm.ny << " " << norm.nz << endl;
            normal.push_back(norm);
        }

        // Check the texture coordinates of the object
        if (prefix == "vt"){
            iss >> tex.u >> tex.v;
            //debug
           // cout << "Texture coordinates: " << tex.u << " " << tex.v << endl;
            texCoord.push_back(tex);
        }

        if (prefix == "f"){

            //Create vertices for the vertices, normals and texture coordinates
             vector < unsigned int> vertexIndex, normalIndex, texCoordIndex;
            // Read the indexes of the vertices
             unsigned int vIndex, nIndex, tIndex;

            char slash;

            // Read the through the indexes of the vertices
            for (int i = 0; i < 4; i++)
            {
                iss >> vIndex >> slash >> tIndex >> slash >> nIndex;

                //debug
              //  cout << vIndex << slash << tIndex << slash << nIndex << endl;
                vertexIndex.push_back(vIndex);
                texCoordIndex.push_back(tIndex);
                normalIndex.push_back(nIndex);
            }

            // Read the indexes of the vertices
            for (int i = 0; i < vertexIndex.size(); i++)
            {
                f.vertexIndex = vertexIndex[i];
                f.normalIndex = normalIndex[i];
                f.texCoordIndex = texCoordIndex[i];
                face.push_back(f);
            }
            
        }

    }

    // Close the file
    file.close();
    cout << "File closed successfully: " << path << endl;
    
     //take the vertices, normals and texture coordinates and put them in a vector
    for (int i = 0; i < face.size(); i++)
    {
        Position p = position[face[i].vertexIndex - 1];
        TexCoord t = texCoord[face[i].texCoordIndex - 1];
        Normal n = normal[face[i].normalIndex - 1];

        //debug
     //   cout << "Vertex: " << p.x << " " << p.y << " " << p.z << endl;
     //   cout << "Texture: " << t.u << " " << t.v << endl;
    //    cout << "Normal: " << n.nx << " " << n.ny << " " << n.nz << endl;

        vertices.push_back(p.x);
        vertices.push_back(p.y);
        vertices.push_back(p.z);

        vertices.push_back(t.u);
        vertices.push_back(t.v);

        vertices.push_back(n.nx);
        vertices.push_back(n.ny);
        vertices.push_back(n.nz);
    }

    // Create the indices for the vertices
    for (int i = 0; i < face.size(); i += 4)
    { 
        //converting the quadrilateral to two triangles

        // The first triangle is created by taking the first three vertices of the face vector
        indices.push_back(i); // 
        indices.push_back(i + 1);
        indices.push_back(i + 2);

        // The second triangle is created by taking the last three vertices of the face vector
        indices.push_back(i);
        indices.push_back(i + 2);
        indices.push_back(i + 3);
    }
}


 vector <float> Model:: getVertices(){
  return  vertices;
}


 vector <unsigned int>  Model:: getIndices(){
  return indices;
}

