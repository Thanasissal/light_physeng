//
// Created by Thanos on 9/21/2026.
//

#ifndef LIGHT_PHYSENG_CAMERA_H
#define LIGHT_PHYSENG_CAMERA_H
#include "Math.h"


class Camera {
public:
    glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f); //initial position of camera
    glm::vec3 CameraTarget = glm::vec3(0.0f, 0.0f, 0.0f); //where the camera is looking z
    glm::vec3 CameraDirection = glm::normalize(position - CameraTarget); // Direction vector
    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f); //World space up vector
    glm::vec3 CameraRight = glm::normalize(glm::cross(up, CameraDirection)); //right of the camera x
    glm::vec3 CameraUp = glm::normalize(glm::cross(CameraRight, CameraDirection)); //local up y

    glm::mat4 view = glm::lookAt(CameraDirection, position, up);

    glm::mat4 test_camera = view;


    float zoom = 1.0f;
    float fov = 45.0f;



};


#endif //LIGHT_PHYSENG_CAMERA_H