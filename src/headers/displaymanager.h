#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "src/headers/camera.h"

int createDisplay(GLFWwindow** window);

void getDeltaTime();

void setCursorPosCallback(GLFWwindow* window, camera* cam);
void setScrollCallback(GLFWwindow* window, camera* cam);
void setFPSCursor(GLFWwindow* window, bool condition);
