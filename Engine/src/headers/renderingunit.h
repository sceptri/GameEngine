#pragma once

namespace  Engine
{

    class renderingUnit
    {
    public:
        unsigned int vaoID;
        int index = -1;

        renderingUnit();
        renderingUnit(bool gen);
        int genVAO();
        int loadToVAOf(float* vertices, int step, int size);
        int loadIndices(unsigned int* indices, int size);
        void bindVAO();
        void unbindVAO();
        void activateAttribPointer(unsigned int pointer) const;
        void deleteVBOs(bool EBOdel);
        void deleteVAO();

    private:
        unsigned int vboIDs[16] = {0}; //length depends on maximum number of attrib pointers of VAO
        unsigned int EBO;

        bool bound = false;
        bool vboBound = false;
        bool generated = false;

        void createBindEBO();
        void storeDataEBO(int size, const void* arr) const;

        void createVBO();
        void bindVBO();
        void unbindVBO();
        void storeDataVBO(int size, const void* arr) const;

        void linkVBOtoVAOAttrib(unsigned int attrib, int nr, unsigned int type, int stride, unsigned long offset) const;
    };

}
