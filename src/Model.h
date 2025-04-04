#ifndef MODEL_H
#define MODEL_H

#pragma once

#include <iostream>
#include <vector>

using namespace std;

class Model
{
public:

    void loadModel(const char* path); // Load a model from a file
    void createBuffers(); // Create buffers for the model
    void drawModel(); // Draw the model

    vector <float> getVertices(); // Get the vertices of the model
    vector <unsigned int> getIndices(); // Get the indices of the model

    typedef struct{
        float x, y, z; // Vertex coordinates
    } Position;

    typedef struct{
        float nx, ny, nz; // Normal vector
    } Normal;

    typedef struct{
        float u, v; // Texture coordinates
    } TexCoord;

    typedef struct{
        unsigned int vertexIndex; // Index of the vertex
        unsigned int normalIndex; // Index of the normal
        unsigned int texCoordIndex; // Index of the texture coordinate
    } Face;
    
    vector <float> vertices; // Vector of vertices
    vector <unsigned int> indices; // Vector of colors


private:
   vector <Position> position;
   vector <Normal> normal;
   vector <TexCoord> texCoord;
   vector <Face> face;
   unsigned int arraySize; // Size of the array

};

#endif