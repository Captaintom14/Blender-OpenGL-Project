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


    // Initialize the Shaders 

    shaders shader;
    shader.createShader("/Users/thomasmejia/Documents/GITHUB DOCUMENTS/Blender-OpenGL-Project/src/vertexShader.vs", "/Users/thomasmejia/Documents/GITHUB DOCUMENTS/Blender-OpenGL-Project/src/fragmentShader.frag");


    // Initialize the Model
    Model model;
    // Load the model from the file (The current file is CUBE.obj and it is for testing purposes once the cybertruck is done, it will be replaced)
    model.loadModel("/Users/thomasmejia/Documents/GITHUB DOCUMENTS/Blender-OpenGL-Project/src/CUBE.obj");



    // Main loop 
    while (!glfwWindowShouldClose(window)) {
        // Clear the screen
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Process input
        processInput(window);

        // Swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }


    // Clean up and exit
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
