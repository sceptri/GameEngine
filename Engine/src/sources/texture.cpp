#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <math.h>
#include <stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "texture.h"

namespace Engine
{

    bool texture::bound = false;

    texture::texture()
    {
        id = 0; //ID 0 CAN'T BE VALID TEXTURE ID
    }

    texture::texture(bool gen)
    {
        if(gen)
        {
            glGenTextures(1, &id);
            generated = true;
        }
    }

    int texture::genTexture()
    {
        if(!generated)
        {
            glGenTextures(1, &id);
            return id;
        }
        else
        {
            std::cout << "ERROR::TEXTURE_ALREADY_GENERATED" << std::endl;
            return -1;
        }
    }

    void texture::flipVertically()
    {
        //set all images to be flipped to have origin in the bottom left corner
        stbi_set_flip_vertically_on_load(true);
    }

    void texture::bindTexture()
    {
        if(!bound)
        {
            glBindTexture(GL_TEXTURE_2D, id);
            bound = true;
        }
        else
        {
            std::cout << "ERROR::TEXTURE_ALREADY_BOUND" << std::endl;
            return;
        }
    }

    void texture::unbindTexture()
    {
        glBindTexture(GL_TEXTURE_2D, 0);
        bound = false;
    }

    void texture::setTextureWrappingAndFiltering() const
    {
        if(bound)
        {
            //set texture wrapping/filtering options only on the currently bound texture
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        }
        else
        {
            std::cout << "ERROR::TEXTURE_NOT_BOUND::CANNOT_SET_FILTERING_AND_WRAPPING" << std::endl;
            return;
        }
    }

    void texture::loadTexture(const char* adress, unsigned int colorType)
    {
        if(bound)
        {
            //loading image into memory and then passing pointer to it
            int width, height, nrChannels;
            unsigned char* data = stbi_load(adress, &width, &height, &nrChannels, 0);

            if(data)
            {
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, colorType, GL_UNSIGNED_BYTE, data); //loading texture data into bound texture
                glGenerateMipmap(GL_TEXTURE_2D); //generating mipmap
            }
            else
            {
                std::cout << "ERROR::FAILED_TO_LOAD_TEXTURE" << std::endl;
            }
            stbi_image_free(data);
        }
        else
        {
            std::cout << "ERROR::TEXTURE_NOT_BOUND::CANNOT_LOAD_TEXTURE" << std::endl;
            return;
        }
    }

    void texture::bindTextureToSlot(unsigned int nr)
    {
        glActiveTexture(nr);
        bound = false;
        bindTexture();
    }

    void texture::deleteTexture()
    {
        glDeleteTextures(1, &id);
    }

}
