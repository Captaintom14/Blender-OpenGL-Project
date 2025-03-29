#include "shaders.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <iostream>
#include <fstream>

using namespace std;

void shaders::createShader(const char* vertexPath, const char* fragmentPath)
{
   unsigned int vertexShader, fragmentShader;
    
   // Read the vertex shader code from the file
    string vertexCode;
    ifstream vShaderFile;
    vShaderFile.exceptions(ifstream::failbit | ifstream::badbit); // Enable exceptions
    try {
        vShaderFile.open(vertexPath);
        stringstream vShaderStream;
        vShaderStream << vShaderFile.rdbuf();
        vertexCode = vShaderStream.str();
        vShaderFile.close();
    }
    catch (ifstream::failure e) {
        cout << "ERROR::SHADER::VERTEX::FILE_NOT_SUCCESSFULLY_READ" << endl;
    }
    const char* vShaderCode = vertexCode.c_str();

    int successVertex; 
    char infoLogVertex[512];
    // Compile vertex shader
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &successVertex);
    if (!successVertex) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLogVertex);
        cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLogVertex << endl;
    }
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vShaderCode, NULL);
    glCompileShader(vertexShader);

    // Read the fragment shader code from the file
    string fragmentCode;
    ifstream fShaderFile;
    fShaderFile.exceptions(ifstream::failbit | ifstream::badbit); // Enable exceptions
    try {
        fShaderFile.open(fragmentPath);
        stringstream fShaderStream;
        fShaderStream << fShaderFile.rdbuf();
        fragmentCode = fShaderStream.str();
        fShaderFile.close();
    }
    catch (ifstream::failure e) {
        cout << "ERROR::SHADER::FRAGMENT::FILE_NOT_SUCCESSFULLY_READ" << endl;
    }

    const char* fShaderCode = fragmentCode.c_str();
    int successFragment;
    char infoLogFragment[512];
    // Compile fragment shader
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &successFragment);
    if (!successFragment) {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLogFragment);
        cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLogFragment << endl;
    }

    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fShaderCode, NULL);
    glCompileShader(fragmentShader);

    // Create the shader program
    ID = glCreateProgram();
    glAttachShader(ID, vertexShader);
    glAttachShader(ID, fragmentShader);
    glLinkProgram(ID);


    // Delete the shaders
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}


void shaders::useShader()
{
    glUseProgram(ID);
}

