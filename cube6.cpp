#include <GLES2/gl2.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

GLfloat vertices[] = {
    -0.5f, -0.5f, -0.5f,
     0.5f, -0.5f, -0.5f,
     0.5f,  0.5f, -0.5f,
    -0.5f,  0.5f, -0.5f,
    -0.5f, -0.5f,  0.5f,
     0.5f, -0.5f,  0.5f,
     0.5f,  0.5f,  0.5f,
    -0.5f,  0.5f,  0.5f
};

GLuint indices[] = {
    0,1,2,
    0,2,3,
    4,5,6,
    4,6,7,
    1,2,6,
    1,5,6,
    0,3,4,
    3,4,7,
    0,1,5,
    0,4,5,
    2,3,6,
    3,6,7
};

const char* vertexShaderSource = R"(
    attribute vec3 position;
    uniform mat4 model;
    uniform mat4 view;
    uniform mat4 projection;
    varying vec3 fragColor;
    void main() {
        gl_Position = projection * view * model * vec4(position, 1.0);
        fragColor = position;
    }
)";

const char* fragmentShaderSource = R"(
    varying vec3 fragColor;
    void main() {
         gl_FragColor = vec4(fragColor, 1.0);
    }
)";

// Küpün pozisyonu
glm::vec3 cubePosition(0.0f, 0.0f, 0.0f);
// Küpün ölçeği
glm::vec3 cubeScale(1.0f, 1.0f, 1.0f);
// Yükseklik hareket hızı
float moveSpeed = 0.05f;
// Ölçekleme hızı
float scaleSpeed = 0.05f;

// GLFW klavye tuşları için geri çağrı işlevi
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (action == GLFW_PRESS || action == GLFW_REPEAT) {
        switch (key) {
        case GLFW_KEY_UP:
            cubeScale += glm::vec3(scaleSpeed, scaleSpeed, scaleSpeed);
            break;
        case GLFW_KEY_DOWN:
            cubeScale -= glm::vec3(scaleSpeed, scaleSpeed, scaleSpeed);
            break;
        case GLFW_KEY_W:
            cubePosition.y += moveSpeed;
            break;
        case GLFW_KEY_S:
            cubePosition.y -= moveSpeed;
            break;
        case GLFW_KEY_A:
            cubePosition.x -= moveSpeed;
            break;
        case GLFW_KEY_D:
            cubePosition.x += moveSpeed;
            break;
        }
    }
}

int main() {
    if (!glfwInit()) {
        return -1;
    }

    GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL Cube", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, keyCallback);

    glEnable(GL_DEPTH_TEST);

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    glUseProgram(shaderProgram);

    GLuint VBO, EBO;
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
    glEnableVertexAttribArray(posAttrib);
    glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);

    GLint modelLoc = glGetUniformLocation(shaderProgram, "model");
    GLint viewLoc = glGetUniformLocation(shaderProgram, "view");
    GLint projectionLoc = glGetUniformLocation(shaderProgram, "projection");

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(1.0f,1.0f,1.0f,1.0f);

        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, cubePosition);
        model = glm::scale(model, cubeScale);
        model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.5f, 1.0f, 0.0f));

        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

        glm::mat4 view = glm::lookAt(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

        glm::mat4 projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    glDeleteProgram(shaderProgram);

    glfwTerminate();

    return 0;
}
