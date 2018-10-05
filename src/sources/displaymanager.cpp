#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "src/headers/displaymanager.h"

void framebuffer_size_callback(GLFWwindow*, int width, int height);

extern int base_width;
extern int base_height;

int createDisplay(GLFWwindow** window)
{
    //glfw initialize and configure
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    //glfw window creation
    *window = glfwCreateWindow(base_width, base_height, "Learn OpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(*window);

    //load OpenGL function pointers
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glViewport(0, 0, base_width, base_height);

    //setting a function that resizes viewport when window modified
    glfwSetFramebufferSizeCallback(*window, framebuffer_size_callback);

    return 1;
}

//resizing screen -> modifying viewport
void framebuffer_size_callback(GLFWwindow*, int width, int height)
{
    glViewport(0,0, width, height);
    base_width = width;
    base_height = height;
}
