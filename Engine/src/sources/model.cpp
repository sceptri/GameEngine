#include "model.h"
#include <iostream>

namespace Engine
{

    bool model::renderPrepared = false;

    inline long INDEX(unsigned long x){return x-GL_TEXTURE0;} //makes index(of textures array) from OpenGL tex slot
    inline long TEX(int x){return x+GL_TEXTURE0;}//reverse to IDNEX func

    model::model()
    {
        for(int i = 0; i < 32; i++)
        {
            texSlots[i] = -1;
            textures[i] = texture();
        }

    }

    void model::loadRUnit(renderingUnit *rendUnit)
    {
        (*rendUnit).unbindVAO();
        rUnit = *rendUnit;
        rUnit.bindVAO();
    }

    void model::loadTexture(texture texture, unsigned long texSlot)
    {
        if(INDEX(texSlot) > 31)
        {
            std::cout << "[ERROR]::TEXTURE_SLOT_OUT_OF_BOUNDS::CANNOT_LOAD_TEXTURE" << std::endl;
            return;
        }
        if(texSlots[INDEX(texSlot)] != -1)
        {
            std::cout << "[ERROR]::TEXTURE_SLOT_NOT_VACANT::CANNOT_LOAD_TEXTURE" << std::endl;
            return;
        }

        textures[INDEX(texSlot)] = texture;
        texSlots[INDEX(texSlot)] = texSlot;
    }

    int model::genTexture(const char* adress, unsigned int typeColor)
    {
        //checks if there exists a tex slot, which is not already used
        bool vacant = false;
        int i = 0;
        for(; i < 32; i++)
        {
            if(texSlots[i] == -1)
            {
                vacant = true;
                break;
            }

        }
        if(!vacant)
        {
            std::cout << "[ERROR]::MAXIMUM_NUMBER_OF_TEXTURES::CANNOT_GENERATE_TEXTURE" << std::endl;
            return -1;
        }

        //standart texture generation
        textures[i] = texture(true);
        textures[i].bindTexture();
        textures[i].setTextureWrappingAndFiltering();
        textures[i].loadTexture(adress, typeColor);
        texture::unbindTexture();
        //assignes generated some tex slot
        texSlots[i] = TEX(i);

        std::cout << "[WARNING]::TEXTURE_IMPLICITLY_ASSIGNED_TO_SLOT: " << i << std::endl;
        return i;
    }

    void model::prepareRender()
    {
        //activates and binds all model textures to corespoding OpenGL tex slots
        for(int i = 0; i < 32; i++)
        {
            if(texSlots[i] != -1)
            {
                textures[i].bindTextureToSlot((unsigned int)texSlots[i]);
            }
        }

        rUnit.bindVAO();
    }

    void model::freeRender()
    {
        for(int i = 0; i < 32; i++)
        {
            if(texSlots[i] != -1)
            {
                glActiveTexture(TEX(i));
                glBindTexture(GL_TEXTURE_2D, 0);
                texture::bound = false;
            }
        }

        rUnit.unbindVAO();
    }

    void model::deleteModel(bool EBO)
    {
        rUnit.deleteVBOs(EBO);
        rUnit.deleteVAO();

        for(int i = 0; i < 32; i++)
        {
            if(texSlots[i] != -1)
            {
                textures[i].deleteTexture();
            }
        }
    }

    void model::rotate(float angle, int axis_x, int axis_y, int axis_z, bool rads)
    {
        if(rads)
            modelMat = glm::rotate(modelMat, angle, glm::vec3(axis_x, axis_y, axis_z));
        else
            modelMat = glm::rotate(modelMat, glm::radians(angle), glm::vec3(axis_x, axis_y, axis_z));
    }

    void model::translate(float axis_x, float axis_y, float axis_z)
    {
        modelMat = glm::translate(modelMat, glm::vec3(axis_x, axis_y, axis_z));
    }

}
