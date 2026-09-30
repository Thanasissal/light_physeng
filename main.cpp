#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Camera.h"
#include "Math.h"
#include "Mesh.h"
#include "Shader.h"
#include "Vertex.h"

int main() {

    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    GLFWwindow* window;

    window = glfwCreateWindow(900, 600, "Light Physics Engine", nullptr, nullptr);

    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glEnable(GL_DEPTH_TEST);

    Shader myShader("Shaders/test.vert", "Shaders/test.frag");

    Mesh Triange({
        {glm::vec3(-0.5f, -0.5f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 0.0f)},
        {glm::vec3( 0.5f, -0.5f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 0.0f)},
        {glm::vec3( 0.0f,  0.5f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.5f, 1.0f)}
    },  {0,1,2,3});


    Camera camera;
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), 900.0f / 600.0f, 0.1f, 100.0f);

    myShader.use();
    myShader.setMat4("view", camera.getCurrentView());
    myShader.setMat4("projection", projection);

    // Main render loop
    while (!glfwWindowShouldClose(window)) {
        // 1. CLEAR THE SCREEN AND DEPTH BUFFER EVERY FRAME
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f); // Dark grey background
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // 2. CALCULATE MATRICES
        glm::mat4 model = glm::mat4(1.0f);

        const float radius = 10.0f;
        float camX = sin(glfwGetTime()) * radius;
        float camZ = cos(glfwGetTime()) * radius;
        glm::mat4 view = glm::lookAt(glm::vec3(camX, 0.0, camZ), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));

        // 3. SEND MATRICES TO THE SHADER
        myShader.use(); // Always a good habit to ensure your shader is active before sending uniforms
        myShader.setMat4("view", view);
        myShader.setMat4("model", model);

        Triange.Draw();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
}
