#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Camera.h"
#include "Math.h"
#include "Shader.h"

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

    //VBO
    float vertices[] = {
        // Positions         // Colors
        -0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 1.0f, // 0: Front-left base
        0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 1.0f, // 1: Front-right base
        0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 1.0f, // 2: Back-right base
        -0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 1.0f, // 3: Back-left base
        0.0f,  0.5f,  0.0f,  1.0f, 0.0f, 0.0f  // 4: Top Apex (Red)
    };

    // The Index Buffer telling OpenGL how to connect the vertices above
    unsigned int indices[] = {
        // Base (Two triangles making a square)
        0, 1, 2,
        2, 3, 0,
        // Front face
        0, 1, 4,
        // Right face
        1, 2, 4,
        // Back face
        2, 3, 4,
        // Left face
        3, 0, 4
    };

    unsigned int VBO, VAO, EBO; // Add EBO here
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);      // Generate the EBO

    glBindVertexArray(VAO);

    // 1. Bind and fill VBO
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // 2. Bind and fill EBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // 3. Configure Attributes (This remains exactly the same as before)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);

    Camera camera;
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), 900.0f / 600.0f, 0.1f, 100.0f);

    myShader.use();
    myShader.setMat4("view", camera.test_camera);
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

        // 4. BIND VAO AND DRAW
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 18, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
}
