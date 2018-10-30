#include "glmath.h"

namespace Engine
{
    glm::mat4 projectionMat(float angle, float aspectRatio, float near, float far, bool rads)
    {
        if(rads)
            return glm::perspective(angle, aspectRatio, near, far);
        else
            return glm::perspective(glm::radians(angle), aspectRatio, near, far);
    }
}
