#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <include/stb_image.h>
#include <iostream>

class texture
{
public:
    unsigned int id;
    static bool bound;

    texture();
    texture(bool gen);
    int genTexture();
    void bindTextureToSlot(unsigned int nr);
    void bindTexture();
    static void unbindTexture();
    void loadTexture(const char* adress, unsigned int colorType);
    void setTextureWrappingAndFiltering() const;
    static void flipVertically();
    void deleteTexture();

private:
    bool generated = false;
};
