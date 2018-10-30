#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

namespace Engine
{
    static void glClearError()
    {
        while(glGetError() != GL_NO_ERROR);
    }
    static void glCheckError()
    {
        while(GLenum error = glGetError())
        {
            std::cout << "ERROR: " << error << std::endl;
        }
    }
}
