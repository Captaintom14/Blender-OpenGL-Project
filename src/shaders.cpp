#include "shaders.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <iostream>
#include <sstream>
#include <fstream>

using namespace std;

void shaders::createShader(const char* vertexPath, const char* fragmentPath){

    cout << "Creating Shader..." << endl;
    cout << "DebugShader Vertex Shader Path: " << vertexPath << endl; //debug
    cout << "DebugShader Fragment Shader Path: " << fragmentPath << endl; // debug
   unsigned int vertexShader, fragmentShader;

   // Read the vertex shader code from the file
    cout << "Reading Vertex Shader..." << endl; //debug
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
    cout << "Vertex Shader Code: " << vShaderCode << endl; //debug


    // Compile vertex shader 
    cout << "Compiling Vertex Shader..." << endl; //debug
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    if (vertexShader == 0) {
        cout << "ERROR::SHADER::VERTEX::CREATION_FAILED" << endl;
        return;
    } 

    cout << "Vertex Shader Created Successfully" << endl; //debug
    
    glShaderSource(vertexShader, 1, &vShaderCode, NULL);
    glCompileShader(vertexShader);

    int successVertex; 
    char infoLogVertex[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &successVertex);
    if (!successVertex) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLogVertex);
        cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLogVertex << endl;
    }
    cout << "Vertex Shader Compiled Successfully" << endl; //debug


    
    // Read the fragment shader code from the file
    cout << "Reading Fragment Shader..." << endl; //debug
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
    cout << "Compiling Fragment Shader..." << endl; //debug 
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fShaderCode, NULL);
    glCompileShader(fragmentShader);

     glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &successFragment);
    if (!successFragment) {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLogFragment);
        cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLogFragment << endl;
    }

    cout << "Fragment Shader Compiled Successfully" << endl; //debug

 // Create the shader program

    cout << "Creating Shader Program..." << endl; //debug

    ID = glCreateProgram();
    glAttachShader(ID, vertexShader);
    glAttachShader(ID, fragmentShader);
    glLinkProgram(ID);

    int success;
    char infoLog[512];
    glGetProgramiv(ID, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(ID, 512, NULL, infoLog);
        cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << endl;
        return;
    }

    cout << "Shader Program Linked Successfully" << endl; //debug

    // Delete the shaders
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}


void shaders::useShader()
{
    glUseProgram(ID);
}

