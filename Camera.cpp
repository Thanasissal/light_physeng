//
// Created by Thanos on 9/21/2026.
//

#include "Camera.h"

// Constructor Definition
Camera::Camera() {
    position = glm::vec3(0.0f, 0.0f, 3.0f); // Moved back on the Z axis
    target   = glm::vec3(0.0f, 0.0f, 0.0f); // Looking at the origin

    zoom = 1.0f;
    fov = 45.0f;
}

// Method Definition
glm::mat4 Camera::getCurrentView() {
    return glm::lookAt(position, target, WORLD_UP);
}