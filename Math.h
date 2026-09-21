//
// Created by Thanos on 9/21/2026.
//

#ifndef LIGHT_PHYSENG_MATH_H
#define LIGHT_PHYSENG_MATH_H

#pragma once

// 1. Core External Library Includes
// Keep these strictly limited to exactly what the engine needs.
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Quaternions are essential for 3D physics rotations to avoid gimbal lock
#include <glm/gtc/quaternion.hpp>

namespace Physics {
    using Vec2 = glm::vec2;
    using Vec3 = glm::vec3;
    using Vec4 = glm::vec4;
    using Mat3 = glm::mat3;
    using Mat4 = glm::mat4;
    using Quat = glm::quat;

    inline float Dot(const Vec3& a, const Vec3& b) { return glm::dot(a, b); }
}

#endif //LIGHT_PHYSENG_MATH_H