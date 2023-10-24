
# OpenGL Cube

This project is a sample application that uses GLFW and OpenGL to create a 3D graphical rendering of a simple cube and allows the user to scale the cube, move it up and down and left and right with keyboard inputs. Below is a description of the basic features and working logic of the project:

#### 1. Libraries and Initialization Settings:

- Libraries such as **`GLES2/gl2.h`**, **`GLFW/glfw3.h`**, **`glm/glm.hpp`** are included in the project. These libraries are used for OpenGL operations and window management.
- A set of initialization variables are defined, such as **`vertices`** (vertices of the cube), **`indices`** (indices for rendering the cube), **`vertexShaderSource`** and **`fragmentShaderSource`** (shader code for rendering the cube).

#### 2. GLFW Window Creation:

- GLFW is started and a window is created. The window title is set to "OpenGL Cube".
- The **`keyCallback`** function is assigned as the event handling function. This function processes keyboard inputs and controls the scaling and movement of the cube.

#### 3. OpenGL Settings:

- We enable depth testing so that the surfaces of the cube are drawn correctly.
- Shader programs are created and compiled.
- Vertex Buffer Object (VBO) and Element Buffer Object (EBO) are created and the vertices and indices of the cube are loaded into these buffers.
- Use **`glGetAttribLocation`** and **`glGetUniformLocation`** to get the position attribute and uniforms from the shader program.

#### 4. Main Loop:

- The main loop contains a loop that runs until the window is closed.
- At each loop step, the OpenGL window is cleared, the background color is set and a model matrix is calculated. The model matrix contains the position, scale and rotation of the cube.
- A camera view matrix and a projection matrix are created. These matrices represent the position of the camera in the world and its perspective projection.
- The model, view and projection matrices are loaded into the shader program.
- The cube is drawn with the **`glDrawElements`** function and the drawing is sent to the window with **`glfwSwapBuffers`**.
- The user's keyboard inputs are processed by the **`keyCallback`** function and the scaling and movement of the cube is updated according to these inputs.

#### 5. Cleanup and Close:

- When the program ends, the generated OpenGL buffers and shader programs are cleared.
- GLFW is closed and the program ends.

This project shows how to create a basic 3D graphics application. It includes many basic concepts that you can use to develop 3D graphics programs using OpenGL.

### How is the transformation applied to the cube?

In this project, the transform operations applied to the cube are performed using the model matrix, the view matrix and the projection matrix. Here is a detailed explanation of how these transformations are applied:

#### 1. Model Matrix:
The model matrix represents the position, scale and rotation of the cube. This matrix is used to change the position and shape of the cube in world coordinates.

- First, an empty model matrix is created: **`glm::mat4 model = glm::mat4(1.0f);`**. This matrix starts as a unit matrix.
- The position of the cube is added to the model matrix with **`glm::translate`**. This represents the movement of the cube in world coordinates.
- The scale of the cube is added to the model matrix with **`glm::scale`**. This changes the size of the cube.
- The rotation of the cube is added to the model matrix with **`glm::rotate`**. This represents the rotation of the cube.

These operations represent transformations applied to the model matrix and at each drawing step this matrix is loaded into the shader program to change the appearance of the cube.

#### 2. View Matrix:
The view matrix indicates where we are in world coordinates and where we are looking. This matrix represents the position of the camera and the direction of view.

- The **`glm::lookAt`** function creates the view matrix. The first parameter is the position of the camera, the second parameter is where to look, and the third parameter is the upward vector of the camera.

#### 3. Projection Matrix:
The projection matrix determines how the scene is displayed. This matrix defines perspective projection.

- The **`glm::perspective`** function creates the projection matrix. The first parameter specifies the viewing angle, the second parameter specifies the aspect ratio of the screen, the third parameter specifies the closest distance at which the rendering starts and the last parameter specifies the maximum distance at which the rendering ends.

#### 4. Sending Matrices to the Shader Program:
At each drawing step, the generated model, view and projection matrices are loaded into the shader program. This updates the location, shape and appearance of the cube.

- The **`glUniformMatrix4fv`** function loads the model matrix **`modelLoc`**, the view matrix **`viewLoc`** and the projection matrix **`projectionLoc`** into the uniforms. These matrices are used in the vertex shader and change the appearance of the cube.

In this way, the model matrix sets the position, scale and rotation of the cube in world coordinates, the view matrix sets the position and direction of view of the camera, and the projection matrix sets the perspective projection. These matrices are updated at each drawing step and the appearance of the cube is changed so that it can move, rotate and scale.

### What are the glm and its functions doing in the background while the transform operations are happening?

The **`glm`** library is a C++ library designed to facilitate the math operations used in OpenGL. This library is typically used in 3D graphics projects to perform mathematical calculations such as matrix operations, vector operations, and transform operations. Here are a few important explanations of what the **`glm`** library does in the background:

#### 1. Data Structures:
- The **`glm`** library contains mathematical data structures used to represent 2D and 3D mathematical objects. For example, **`glm::vec3`** vectors, **`glm::mat4`** matrices. These data structures are used to represent mathematical operations in OpenGL.

#### 2. Mathematical Operations:
- **`glm`** functions make it easy to perform operations on these mathematical data structures. For example, operations such as addition, subtraction, inner product, cross product between vectors, multiplication and transformation between matrices are performed with these functions.

#### 3. Matrix and Vector Multiplication:

- Multiplying two matrices or a matrix by a vector mathematically involves the addition of each element. For example, multiplying two matrices requires multiplying each element in turn and summing the results.
- **`glm`** does this by using appropriately defined operators between the matrix and vector data structures. For example, multiplying **`glm::mat4`** by **`glm::vec4`** correctly computes the result of this operation.

#### 4. Matrix Operations:

- Matrix operations include basic mathematical operations such as addition, subtraction, multiplication, transposition of matrix elements. These operations are performed in the background by applying them to the elements of the matrix.

#### 5. Vector Operations:

- Vector operations include operations such as addition, subtraction, inner product, cross product calculation of vector elements. These operations are also performed on vector elements.

#### 6. Transformation Operations:

- Transform operations perform basic features of 3D graphics, such as movement, rotation and scaling of objects using matrix multiplications. For example, multiplying the position of an object by a matrix allows the object to be moved to a specific position.

#### 7. Optimizations

- **`glm`** implements various compile-time optimizations to make mathematical operations more efficient. This ensures that calculations are done quickly and efficiently.

To summarize, the **`glm`** library is a tool for performing mathematical operations in 3D graphics applications and is compatible with OpenGL. This library allows you to easily and efficiently perform basic mathematical operations such as matrix operations, transform operations and vector operations, so you can perform complex mathematical calculations with less difficulty when rendering 3D scenes.

### For example, what happens in the background in `glm::translate` `glm::rotate` and `glm::scale` functions?

The **`glm::translate`**, **`glm::rotate`**, and **`glm::scale`** functions in the glm library allow you to easily move, rotate, and scale 3D objects. The basic mathematical operations behind these functions are as follows:

#### Background of `glm::translate`:
- In **`glm::translate`**, a translation matrix is added to a model matrix data structure. This translate matrix allows the object to move in a specific direction.
- The translation matrix is a 4x4 matrix and is defined as follows:
```bash
1 0 0 X
0 1 0 Y
0 0 1 Z
0 0 0 1
```
- X, Y and Z represent the distance the object will be shifted in a given direction. **`glm::translate`** adds this translation matrix to the existing model matrix.

#### Background of `glm::rotate`:

- In **`glm::rotate`**, a rotation matrix is added to a model matrix data structure. This rotation matrix allows the object to rotate on a specific axis.
- The rotation matrix is a 4x4 matrix and is defined as follows (for example, rotation on the Z axis):
```bash
cos(theta) -sin(theta) 0 0
sin(theta) cos(theta)  0 0
0          0           1 0
0          0           0 1
```
- Here, theta is the rotation angle. **`glm::rotate`** adds this rotation matrix to the existing model matrix.

#### Background of glm::scale:

- In **`glm::scale`**, a scaling matrix is added to a model matrix data structure. This scaling matrix changes the size of the object.
- The scaling matrix is a 4x4 matrix and is defined as follows:
```bash
X 0 0 0
0 Y 0 0
0 0 Z 0
0 0 0 1
```
- X, Y and Z represent the scaling of the object's dimensions. glm::scale adds this scaling matrix to the existing model matrix.

These functions create the relevant matrices for transforming the model matrix and add these matrices to the current model matrix. As a result, the position, rotation and size of the object are updated through these transformation matrices and the image of the object is modified. These functions are widely used in 3D graphics applications for moving, rotating and scaling objects.

### How to add these transform matrices to the model matrix?

- When adding transform matrices (translation, rotation, scaling matrices) to the model matrix, these matrices need to be multiplied in turn and applied to the model matrix. This ensures that the matrices are combined to contain all the transformations that affect the final appearance of the object. Here is an example of how to perform this operation:
```cpp
glm::mat4 model = glm::mat4(1.0f); // An empty model matrix is created.

// Add the translation matrix to the model matrix (e.g. shift 2 units to the right on the X axis):

glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(2.0f, 0.0f, 0.0f));
model = model * translationMatrix;

// Add the rotation matrix to the model matrix (e.g. rotate by 45 degrees):

glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
model = model * rotationMatrix;

// Adding the scaling matrix to the model matrix (e.g. doubling its size):

glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(2.0f, 2.0f, 2.0f));
model = model * scaleMatrix;
```
- In the example above, each transform matrix (flip, rotate, scale) is created separately and then multiplied by the model matrix. This process is performed sequentially so that the final view of the object contains all transformations.

As a result, the model matrix becomes a transformation matrix that includes the operations of translation, rotation and scaling. This model matrix represents the position, rotation and size of the object in world coordinates. The model matrix is then used to place and render the object in world coordinates. This is a common method for moving, rotating and scaling objects in 3D graphics.

## Prerequisites
Before running this project, make sure the following dependencies and packages are installed:

1. [OpenGL ES2.0](https://www.khronos.org/opengles/) is a graphics library for graphics processing. Some packages may be required to enable OpenGL ES 2.0 support on Linux systems. You can install the required packages with the following command:
```bash
sudo apt-get install libgles2
```
2. [GLFW 3.3](https://www.glfw.org/) is a library for window rendering and user input. You can use the following command to install GLFW:
```bash
sudo apt-get install libglfw3
```
3. [glm](https://github.com/g-truc/glm) (OpenGL Mathematics) is a header file library for performing mathematical operations in OpenGL projects. You can use the following command to install GLM:
```bash
sudo apt-get install libglm-dev
```

## Installation and Usage
To get started, follow these steps:
1. Clone the repository:
```bash
git clone https://github.com/yesillmustafa/cube.git
```
2. Navigate to the repository folder:
```bash
cd cube
```
3. Build the program using a C++ compiler (e.g., g++):  
- There are 6 executable cube codes in the repository, so you need to compile and run whichever code you want to compile. (e.g. I want to compile cube6.cpp)
```bash
g++ -o cube6 cube6.cpp -lglfw -lGLESv2
```
4. Run the program: 
```bash
./cube6
```
5. Use the "W","A","S","D" keys to move and arrow keys to scale.
