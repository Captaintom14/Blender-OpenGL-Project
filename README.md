# CyberTruck OpenGL Project 

A sample OpenGL Application that loA sample OpenGL application that loads and renders a 3D model (e.g., a CyberTruck) exported from Blender. This project uses GLFW for window/context creation, GLEW for managing OpenGL extensions, and GLM for matrix operations and transformations.

## Features
- **OBJ Model Loader**: Loads a single mesh from an OBJ file, including vertex positions, texture coordinates, and normals thanks to the Assimp Library

- **Quad-to-Triangle Conversion** : Automatically triangulates quad faces from the OBJ file into triangles.

- **Shader Pipeline** : Uses a vertex shader for transforming model, view, and projection matrices and a fragment shader for basic coloring

- **User Input** : Supports keyboard controls to translate, scale, and rotate the model.

- **Initial Rotation** : Allows setting a default rotation before the window launches.

## Requirements
- **C++ Compiler** : A modern C++ compiler supporting C++ 11 or later
- **OpenGL** : Version 3.3 or higher
- **GLEW** : The OpenGL Extension Wrangler Library
- **GLFW** : The GLFW Library
- **GLM** : OpenGL Mathematics 
