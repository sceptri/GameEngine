#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "camera.h"

namespace Engine
{
    int createDisplay(GLFWwindow** window, int * width, int * height, float * last, float * delta);

    void getDeltaTime();

    void setCursorPosCallback(GLFWwindow* window, camera* cam);
    void setScrollCallback(GLFWwindow* window, camera* cam);
    void setFPSCursor(GLFWwindow* window, bool condition);
}
