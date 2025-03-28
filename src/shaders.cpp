#include "shaders.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <iostream>
#include <fstream>

using namespace std;

void shaders::createShader(const char* vertexPath, const char* fragmentPath)
{
   
}


void shaders::useShader()
{
    glUseProgram(ID);
}
void shaders::setBool(const char* name, bool value)
{
    glUniform1i(glGetUniformLocation(ID, name), (int)value);
}
void shaders::deleteShader()
{
    glDeleteProgram(ID);
}
void shaders::setInt(const char* name, int value)
{
    glUniform1i(glGetUniformLocation(ID, name), value);
}

