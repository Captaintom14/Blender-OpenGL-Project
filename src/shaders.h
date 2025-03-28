#ifndef SHADERS_H
#define SHADERS_H

#pragma once

class shaders
{
public:

void createShader(const char* vertexPath, const char* fragmentPath); //Create a Shader based on the paths to the vertex and fragment shader

void useShader(); //Use the shader program
void setBool(const char* name, bool value); //Set a boolean uniform in the shader
void deleteShader(); // Delete the shader program

void setInt(const char* name, int value); //Set an integer uniform in the shader
void setFloat(const char* name, float value); //Set a float uniform in the shader


private:

unsigned int ID;

};

#endif