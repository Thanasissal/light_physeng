//
// Created by Thanos on 9/30/2026.
//

#pragma once
#define LIGHT_PHYSENG_MESH_H
#include "Math.h"
#include "Vertex.h"

class Mesh {
    private:
        unsigned int VAO, VBO, EBO;

        void setupMesh();

    public:
        std::vector<Vertex> vertices;
        std::vector<unsigned int> indices;

        Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices);

        void Draw();
};
