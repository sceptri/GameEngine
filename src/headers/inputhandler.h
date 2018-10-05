#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

void processInput(GLFWwindow* window, int key, void(*func)(GLFWwindow* window));

void closeWindow(GLFWwindow* window);
