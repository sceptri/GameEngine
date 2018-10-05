#include <glad/glad.h>
#include <GLFW/glfw3.h>

//setting esc to close window
void processInput(GLFWwindow* window, int key, void(*func)(GLFWwindow* window))
{
    if(glfwGetKey(window, key)== GLFW_PRESS)
    {
        func(window);
    }
}

void closeWindow(GLFWwindow* window)
{
    glfwSetWindowShouldClose(window, true);
}

