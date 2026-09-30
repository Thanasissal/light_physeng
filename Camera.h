//
// Created by Thanos on 9/21/2026.
//
#pragma once
#define LIGHT_PHYSENG_CAMERA_H
#define WORLD_UP glm::vec3(0.0f, 1.0f, 0.0f)
#include "Math.h"


class Camera {
    private:
        glm::vec3 position;
        glm::vec3 target;

        float zoom;
        float fov;

    public:
        // Constructor
        Camera();

        // Method to get the view matrix
        glm::mat4 getCurrentView();
};