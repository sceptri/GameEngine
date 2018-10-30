#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "texture.h"
#include "renderingunit.h"

namespace Engine
{
    class model
    {
    public:
        static bool renderPrepared;

        renderingUnit rUnit;
        glm::mat4 modelMat;

        model();
        void loadRUnit(renderingUnit *rendUnit);
        void loadTexture(texture texture, unsigned long texSlot);

        int genTexture(const char* adress, unsigned int typeColor);

        void rotate(float angle, int axis_x, int axis_y, int axis_z, bool rads);
        void translate(float axis_x, float axis_y, float axis_z);

        void prepareRender();
        void freeRender();

        void deleteModel(bool EBO);

    private:
        texture textures[32];
        long texSlots[32];
    };
}
