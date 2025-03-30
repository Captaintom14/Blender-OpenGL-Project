#include "Model.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>
using namespace std;


void Model::loadModel(const char* path){

   vector <Position> position;
   Position pos;

   vector <Color> color;
   Color col;

   vector <Normal> normal;
   Normal norm;

   vector <TexCoord> texCoord;
   TexCoord tex;

   vector <Face> face;
   Face f;

   //Open the model file
    string line;
    string name;
    ifstream file(path);
    if (!file.is_open()) {
        cout << "Error opening file: " << path << endl;
        return;
    }

    while (getline(file,line)){

        istringstream iss(line);
        string prefix;

        // Read the first word of the line
        iss >> prefix;

        // Check the name of the object
        if (prefix == "o"){
            iss >> name;
        }
        
        // Check the position of the object
        if (prefix == "v"){
            iss >> pos.x >> pos.y >> pos.z;
            position.push_back(pos);
        }

        // Check the vertex normal of the object
        if (prefix == "vn"){
            iss >> norm.nx >> norm.ny >> norm.nz;
            normal.push_back(norm);
        }

        // Check the texture coordinates of the object
        if (prefix == "vt"){
            iss >> tex.u >> tex.v;
            texCoord.push_back(tex);
        }
        

    }






}



