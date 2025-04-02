#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

#include "Model.h"
#include "shaders.h"
using namespace std;


float xPosition = 0;
float yPosition = 0;
float scale = 1.0f;
float angle = 0.0f;

void movementModel(GLFWwindow* window);

void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
        glfwSetWindowShouldClose(window, true);
    }
    movementModel(window);
}


void movementModel(GLFWwindow* window) {

// if the user presses up
   if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        
    yPosition+=0.010f;
}
// if the user presses down
if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
    yPosition-=0.010f;
}

// if the user presses left
if (glfwGetKey (window, GLFW_KEY_A) == GLFW_PRESS) {
    xPosition-=0.010f;
}

// if the user presses right
if (glfwGetKey (window, GLFW_KEY_D) == GLFW_PRESS) {
    xPosition+=0.010f;
}

// if the user presses 1... it scales the model positively
if (glfwGetKey (window, GLFW_KEY_1) == GLFW_PRESS) {
    scale+=0.010f;
}

// if the user presses 2... it scales the model negatively
if (glfwGetKey (window, GLFW_KEY_2) == GLFW_PRESS) {
    scale-=0.010f;
}

// if the user presses 3... it rotates the model positively
if (glfwGetKey (window, GLFW_KEY_3) == GLFW_PRESS) {
    angle+=glm::radians(2.0f);
}

// if the user presses 4... it rotates the model negatively
if (glfwGetKey (window, GLFW_KEY_4) == GLFW_PRESS) {
    angle-=glm::radians(2.0f);
}

}



int main() {
     
    if (!glfwInit()) {
        cout << "Failed to initialize GLFW" << endl;
        return -1;
    }
    cout << "GLFW initialized successfully" << endl; // debug

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL Window", NULL, NULL);
    if (!window) {
        cout << "Failed to create GLFW window" << endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    
    int heightWindow, widthWindow;
    glfwGetWindowSize(window, &widthWindow, &heightWindow);
    glViewport(0, 0, widthWindow, heightWindow);

   
    
    cout << "GLFW window created successfully" << endl; // debug


    // Initialize GLEW
    glewExperimental = GL_TRUE; // Allow modern OpenGL functions
    GLenum err = glewInit();
    if (err != GLEW_OK) {
        cout << "Failed to initialize GLEW: " << glewGetErrorString(err) << endl;
        return -1;
    }
    cout << "GLEW initialized successfully" << endl; // debug


    // Initialize the Shaders 
    shaders shader;
    
   const char* vertexPath = "/Users/thomasmejia/Documents/GITHUB DOCUMENTS/Blender-OpenGL-Project/src/vertexShader.vs";
   const char* fragmentPath = "/Users/thomasmejia/Documents/GITHUB DOCUMENTS/Blender-OpenGL-Project/src/fragmentShader.frag";

    //debug
    cout << " Debug Vertex Shader Path: " << vertexPath << endl;
    cout << " Debug Fragment Shader Path: " << fragmentPath << endl;

    shader.createShader(vertexPath,fragmentPath);


    // Initialize the Model
    Model model;
   const char* modelPath = "/Users/thomasmejia/Documents/GITHUB DOCUMENTS/Blender-OpenGL-Project/src/CUBE.obj";
    //debug
    cout << "Model Path: " << modelPath << endl;
    // Load the model from the file (The current file is CUBE.obj and it is for testing purposes once the cybertruck is done, it will be replaced)
    model.loadModel("/Users/thomasmejia/Documents/GITHUB DOCUMENTS/Blender-OpenGL-Project/src/CUBE.obj");

    
     cout << "Model loaded successfully" << endl;

 
     vector <float> vertices = model.getVertices();
     vector <unsigned int> indices = model.getIndices();





    // Main loop 
    while (!glfwWindowShouldClose(window)) {
        // Clear the screen
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Process input
        processInput(window);
        
        // Use the shader program
        shader.useShader();

        // Swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }


    // Clean up and exit
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
