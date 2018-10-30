#include "inputhandler.h"

namespace Engine
{
    bool processInput(GLFWwindow* window, int key)
    {
        if(glfwGetKey(window, key) == GLFW_PRESS)
            return true;
        else
            return false;
    }

    void closeWindow(GLFWwindow* window)
    {
        glfwSetWindowShouldClose(window, true);
    }
}
