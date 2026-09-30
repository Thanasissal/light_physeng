//
// Created by Thanos on 9/30/2026.
//

#include "Mesh.h"

#include "glad/glad.h"
// Constructor
Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices)
{
    this->vertices = vertices;
    this->indices = indices;

    // Configure the OpenGL buffers immediately upon creation
    setupMesh();
}

void Mesh::setupMesh()
{
    // 1. Generate the IDs for our buffers
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    // 2. Bind the VAO first. All subsequent VBO/EBO bindings and
    //    attribute configurations will be stored inside this VAO.
    glBindVertexArray(VAO);

    // 3. Load data into the VBO
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // A std::vector is contiguous memory, so &vertices[0] acts like a raw array pointer
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

    // 4. Load data into the EBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

    // 5. Configure the Vertex Attributes using offsetof

    // Layout 0: Position (vec3 = 3 floats)
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

    // Layout 1: Normal (vec3 = 3 floats)
    glEnableVertexAttribArray(1);
    // offsetof looks at the Vertex struct and calculates the byte offset of 'Normal' (which is 12)
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));

    // Layout 2: Texture Coordinates (vec2 = 2 floats)
    glEnableVertexAttribArray(2);
    // offsetof calculates the byte offset of 'TexCoords' (which is 24)
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));

    // 6. Unbind the VAO to prevent accidental modification elsewhere
    glBindVertexArray(0);
}

// The Draw Method
void Mesh::Draw()
{
    // Bind our specific VAO
    glBindVertexArray(VAO);

    // Draw the elements based on the indices we provided
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

    // Unbind
    glBindVertexArray(0);
}