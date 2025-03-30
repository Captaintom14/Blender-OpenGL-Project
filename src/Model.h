#ifndef MODEL_H
#define MODEL_H

#pragma once

class Model
{
public:
    void loadModel(const char* path); // Load a model from a file
    
    typedef struct{
        float x, y, z; // Vertex coordinates
    } Position;

    typedef struct{
        float r, g, b; // Color
    } Color;

    typedef struct{
        float nx, ny, nz; // Normal vector
    } Normal;

    typedef struct{
        float u, v; // Texture coordinates
    } TexCoord;

    typedef struct{
        int vertexIndex; // Index of the vertex
        int normalIndex; // Index of the normal
        int texCoordIndex; // Index of the texture coordinate
    } Face;




    
private:

};

#endif