#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "src/headers/renderingunit.h"
#include "src/headers/errorhandler.h"


renderingUnit::renderingUnit()
{
}

renderingUnit::renderingUnit(bool gen)
{
    if(gen)
    {
        glGenVertexArrays(1, &vaoID);
        generated = true;
    }
}

int renderingUnit::genVAO()
{
    if(!generated)
    {
        glGenVertexArrays(1, &vaoID);
        generated = true;
        return vaoID;
    }
    else
    {
        std::cout << "[ERROR]: CANNOT GENERATE VAO; VAO ALREADY GENERATED" << std::endl;
        return -1;
    }
}

void renderingUnit::bindVAO()
{
    glBindVertexArray(vaoID);
    bound = true;
}

void renderingUnit::unbindVAO()
{
    glBindVertexArray(0);
    bound = false;
}

int renderingUnit::loadToVAOf(float* arr, int step, int size)
{
    if(bound || index <= 15)
    {
       createVBO();
       bindVBO();
       storeDataVBO(size, arr);
       linkVBOtoVAOAttrib(index, step, GL_FLOAT, step*long(sizeof (float)), 0);
       unbindVBO();
       return index++;
    }
    else if(index > 15)
    {
        std::cout << "[ERROR]: CANNOT LOAD VERTICES; TOO MANY VBOS" << std::endl;
        return -1;
    }
    else
    {
        std::cout << "[ERROR]: CANNOT LOAD VERTICES; VAO NOT BOUND" << std::endl;
        return -1;
    }
}

void renderingUnit::createVBO()
{
    if(index < 0)
    {
        index = 0;
    }
    glGenBuffers(1, &vboIDs[index]);
}

void renderingUnit::bindVBO()
{
    if(!vboBound)
    {
        glBindBuffer(GL_ARRAY_BUFFER, vboIDs[index]);
        vboBound = true;
    }
    else
    {
        std::cout << "[ERROR]: CANNOT BIND VBO; VBO ALREADY BOUND" << std::endl;
        return;
    }
}

void renderingUnit::unbindVBO()
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    vboBound = false;
}

void renderingUnit::storeDataVBO(int size, const void* arr) const
{
    if(vboBound && bound)
    {
        glClearError();
        glBufferData(GL_ARRAY_BUFFER, size, arr, GL_STATIC_DRAW);
        glCheckError();
    }
    else
    {
        std::cout << "[ERROR]: CANNOT STORE DATA IN VBO; VBO OR VAO NOT BOUND" << std::endl;
        return;
    }
}

void renderingUnit::linkVBOtoVAOAttrib(unsigned int attrib, int nr, unsigned int type, int stride, unsigned long offset) const
{
    if (vboBound && bound)
    {
        //specifing arrangment of values in our VBO for vertex shader, enabling 0th attrib array (layout (location = 0) in our shader)
        //Takes data from currently bound buffer to GL_ARRAY_BUFFER and "binds" them to according position in VAO
        glVertexAttribPointer(attrib, nr, type, GL_FALSE, stride, (void*)offset);
    }
    else
    {
        std::cout << "[ERROR]: CANNOT LINK VBO TO VAO ATTRIB; VBO OR VAO NOT BOUND" << std::endl;
        return;
    }
}

int renderingUnit::loadIndices(unsigned int* indices, int size)
{
    if(bound)
    {
        createBindEBO();
        storeDataEBO(size, indices);
        return EBO;
    }
    else
    {
        std::cout << "[ERROR]: CANNOT LOAD INDICES; VAO NOT BOUND" << std::endl;
        return -1;
    }
}

void renderingUnit::createBindEBO()
{
    if(bound)
    {
        glGenBuffers(1, &EBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    }
    else
    {
        std::cout << "[ERROR]: CANNOT BIND EBO; VAO NOT BOUND" << std::endl;
        return;
    }
}

void renderingUnit::storeDataEBO(int size, const void* arr) const
{
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, arr, GL_STATIC_DRAW);
}

void renderingUnit::activateAttribPointer(unsigned int pointer) const
{
    if (bound)
    {
        glEnableVertexAttribArray(pointer);
    }
    else
    {
        std::cout << "[ERROR]: CANNOT ACTIVATE ATTRIB POINTER; VAO NOT BOUND" << std::endl;
        return;
    }
}

void renderingUnit::deleteVBOs(bool EBOdel)
{
    index--; //we have to subtract one from index var because in the of the loadtoVAO func add one to it even if it's never used afterwards
    while(index >= 0)
    {
        glDeleteBuffers(1, &(vboIDs[index--]));
    }
    if(EBOdel)
        glDeleteBuffers(1, &EBO);
}

void renderingUnit::deleteVAO()
{
    glDeleteVertexArrays(1, &vaoID);
}
