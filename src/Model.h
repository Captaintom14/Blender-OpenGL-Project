#ifndef MODEL_H
#define MODEL_H

#pragma once

class Model
{
public:
    void loadModel(const char* path); // Load a model from a file
    void draw(); // Draw the model

    void setTexture(const char* texturePath); // Set the texture for the model
    void setShader(const char* vertexPath, const char* fragmentPath); // Set the shader for the model
    

private:

};

#endif