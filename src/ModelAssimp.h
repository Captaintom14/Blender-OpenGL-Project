#ifndef MODELASSIMP_H
#define MODELASSIMP_H

#pragma once


#include <vector>
#include <iostream>

using namespace std;

class ModelAssimp
{
public:

    // Load model from file
    void LoadModel(const char* path);

    //get the vertices and indices of the model
    vector <float> getVertices();
    vector <unsigned int> getIndices();
    
 


private:
vector <float> vertices; // Vector of vertices
vector <unsigned int> indices; // Vector of colors
unsigned int meshCount; // Number of meshes in the model

};

#endif