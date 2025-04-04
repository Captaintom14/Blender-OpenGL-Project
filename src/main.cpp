#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


#include "Model.h"
#include "shaders.h"
#include "ModelAssimp.h"

#include <vector>  
#include <iostream>
using namespace std;


float xPosition = 0.5f;
float yPosition = 0.3f;
float scale = 1.0f;
float angle = 30.0f;
int widthWindow, heightWindow = 0;


int initGLFW();
int initGLEW();
void movementModel(GLFWwindow* window);
void BufferData(unsigned int &VAO, unsigned int &VBO, unsigned int &EBO, vector<float>& vertices, vector<unsigned int>& indices);
void matrices(shaders& shader);

int initGLFW() {

    if (!glfwInit()) {
        cout << "Failed to initialize GLFW" << endl;
        return -1;
    }
    cout << "GLFW initialized successfully" << endl; // debug

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    return 0;
}

int initGLEW() {
    // Initialize GLEW
    glewExperimental = GL_TRUE;
    GLenum err = glewInit();
    if (err != GLEW_OK) {
        cout << "Failed to initialize GLEW: " << glewGetErrorString(err) << endl;
        return -1;
    }
    cout << "GLEW initialized successfully" << endl; // debug
    return 0;
}

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

void BufferData(unsigned int &VAO, unsigned int &VBO, unsigned int &EBO, vector <float>& vertices, vector <unsigned int>& indices){

    //1. Bind the Vertex Array Object
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    //2. Bind the Vertex Buffer Object
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices[0], GL_STATIC_DRAW);

    //3. Bind the Element Buffer Object
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);


    //4. Set the vertex attribute pointers (location = 0) Position 
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0); // Vertex position
    glEnableVertexAttribArray(0);

    //5. Set the vertex attribute pointers (location = 1) Texture Coordinates
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float))); // Texture coordinates
    glEnableVertexAttribArray(1);

    //6. Set the vertex attribute pointers (location = 2) Normals
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(5 * sizeof(float))); // Normals
    glEnableVertexAttribArray(2);

}

void matrices(shaders& shader) {
   
    glm ::mat4 modelMatrix = glm::mat4(1.0f); // Initialize the model matrix to identity

    modelMatrix = glm::translate(modelMatrix, glm::vec3(xPosition, yPosition, -3.0f)); // Translate the model
    modelMatrix = glm::rotate(modelMatrix, angle, glm::vec3(2.0f, 1.0f, 5.0f)); // Rotate the model
    modelMatrix = glm::scale(modelMatrix, glm::vec3(scale, scale, scale)); // Scale the model
    unsigned int modelLoc = glGetUniformLocation(shader.ID, "model"); // Get the location of the model matrix in the shaderà
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix)); // Send the model matrix to the shader


    glm :: mat4 view = glm :: translate(glm :: mat4(1.0f), glm :: vec3(0.0f, 0.0f, -5.0f)); // Initialize the view matrix to identity
    unsigned int viewLoc = glGetUniformLocation(shader.ID, "view"); // Get the location of the view matrix in the shader
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view)); // Send the view matrix to the shader

    glm :: mat4 projection = glm :: perspective(glm :: radians(45.0f), (float)widthWindow / (float)heightWindow, 0.1f, 100.0f); // Initialize the projection matrix to identity
    unsigned int projectionLoc = glGetUniformLocation(shader.ID, "projection"); // Get the location of the projection matrix in the shader
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection)); // Send the projection matrix to the shader

}

int main() {
     
    // Initialize GLFW
    if (initGLFW() == -1) {
        return -1;
    }
  
    // Create a windowed mode window and its OpenGL context
    GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL Window", NULL, NULL);
    if (!window) {
        cout << "Failed to create GLFW window" << endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);


    // Initialize GLEW
  if (initGLEW() == -1) {
        return -1;
    }


    glfwGetWindowSize(window, &widthWindow, &heightWindow);
    glViewport(0, 0, widthWindow, heightWindow);

    // Initialize the Shaders 
    shaders shader;
   
    // Set the paths to the vertex and fragment shaders
   const char* vertexPath = "/Users/thomasmejia/Documents/GITHUB DOCUMENTS/Blender-OpenGL-Project/src/vertexShader.vs";
   const char* fragmentPath = "/Users/thomasmejia/Documents/GITHUB DOCUMENTS/Blender-OpenGL-Project/src/fragmentShader.frag";

    //debug
   // cout << " Debug Vertex Shader Path: " << vertexPath << endl;
   // cout << " Debug Fragment Shader Path: " << fragmentPath << endl;

    // Create the shader program
    shader.createShader(vertexPath,fragmentPath);


    // Initialize the Model
   const char* modelPath = "/Users/thomasmejia/Documents/GITHUB DOCUMENTS/Blender-OpenGL-Project/src/CUBE.obj";
    //debug
    //cout << "Model Path: " << modelPath << endl;
    // Load the model from the file (The current file is CUBE.obj and it is for testing purposes once the cybertruck is done, it will be replaced)
    Model model;
    model.loadModel("/Users/thomasmejia/Documents/GITHUB DOCUMENTS/Blender-OpenGL-Project/src/CUBE.obj");
    
    ModelAssimp modelAssimp;
    modelAssimp.LoadModel(modelPath);


    cout << "Model loaded successfully" << endl;

 
    // Get the vertices and indices of the model
    vector <float> vertices = modelAssimp.getVertices();
    vector <unsigned int> indices = modelAssimp.getIndices();


    // Create buffers for the model
    unsigned int VAO, VBO, EBO;
    // Create the buffers
    BufferData(VAO, VBO, EBO, vertices, indices);

    // Enable depth testing
    glEnable(GL_DEPTH_TEST);

    // Main loop 
    while (!glfwWindowShouldClose(window)) {
        
        // Process input
        processInput(window);

        // Clear the screen
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        
        // Use the shader program
        shader.useShader();

        // setup the matrices
        matrices(shader);

        glBindVertexArray(VAO); // Bind the VAO
        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0); // Draw the model
        glBindVertexArray(0); // Unbind the VAO

        // Swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }


    // Clean up and exit
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}



