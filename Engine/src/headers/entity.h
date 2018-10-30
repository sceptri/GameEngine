#pragma once

#include "model.h"

namespace Engine
{
    class entity
    {
    public:
        model entityModel;
        glm::mat4 spatialMat;

        void translate(glm::vec3 translationVector);
        void translate(float x, float y, float z);

        void rotate_deg(float angle, glm::vec3 rot_axes);
        void rotate_deg(float angle, float x, float y, float z);

        void rotate_rad(float angle, glm::vec3 rot_axes);
        void rotate_rad(float angle, float x, float y, float z);
    };
}
