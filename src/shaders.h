#ifndef SHADERS_H
#define SHADERS_H


class shaders
{
public:

void createShader(const char* vertexPath, const char* fragmentPath); //Create a Shader based on the paths to the vertex and fragment shader

void useShader(); //Use the shader program
unsigned int ID; //ID of the shader program

private:

};

#endif