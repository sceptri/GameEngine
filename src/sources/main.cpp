/*
 *
 * Revise the code I have written on 15th of october and earlier and maybe rework some parts
 *
 * ADD NOTES:
 *  add explanation in camera.cpp for reverse mouse movement
 *
*/

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <include/stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "src/headers/masterheader.h"

//default value for width and height
int base_width = 800;
int base_height = 600;

float deltaTime = 0;
float lastTime = 0;

bool model::renderPrepared = false;

template<typename... Args>
void sth(Args&&... args)
{

}

template<typename T,typename... Args>
void log(T t, Args... args)
{
    std::cout << t;
    log(args...);
}

int main()
{
    GLFWwindow* window;
    if(createDisplay(&window) < 0)
        return -1;

    //enabling Depth Test
    glEnable(GL_DEPTH_TEST);

    float vertices[] =
    {
        -0.5f,0.5f,-0.5f,
        -0.5f,-0.5f,-0.5f,
        0.5f,-0.5f,-0.5f,
        0.5f,0.5f,-0.5f,

        -0.5f,0.5f,0.5f,
        -0.5f,-0.5f,0.5f,
        0.5f,-0.5f,0.5f,
        0.5f,0.5f,0.5f,

        0.5f,0.5f,-0.5f,
        0.5f,-0.5f,-0.5f,
        0.5f,-0.5f,0.5f,
        0.5f,0.5f,0.5f,

        -0.5f,0.5f,-0.5f,
        -0.5f,-0.5f,-0.5f,
        -0.5f,-0.5f,0.5f,
        -0.5f,0.5f,0.5f,

        -0.5f,0.5f,0.5f,
        -0.5f,0.5f,-0.5f,
        0.5f,0.5f,-0.5f,
        0.5f,0.5f,0.5f,

        -0.5f,-0.5f,0.5f,
        -0.5f,-0.5f,-0.5f,
        0.5f,-0.5f,-0.5f,
        0.5f,-0.5f,0.5f

    };

    float texCoords[] =
    {

        0.0f,0.0f,
        0.0f,1.0f,
        1.0f,1.0f,
        1.0f,0.0f,
        0.0f,0.0f,
        0.0f,1.0f,
        1.0f,1.0f,
        1.0f,0.0f,
        0.0f,0.0f,
        0.0f,1.0f,
        1.0f,1.0f,
        1.0f,0.0f,
        0.0f,0.0f,
        0.0f,1.0f,
        1.0f,1.0f,
        1.0f,0.0f,
        0.0f,0.0f,
        0.0f,1.0f,
        1.0f,1.0f,
        1.0f,0.0f,
        0.0f,0.0f,
        0.0f,1.0f,
        1.0f,1.0f,
        1.0f,0.0f


    };

    unsigned int indices[] =
    {
        0,1,3,
        3,1,2,
        4,5,7,
        7,5,6,
        8,9,11,
        11,9,10,
        12,13,15,
        15,13,14,
        16,17,19,
        19,17,18,
        20,21,23,
        23,21,22

    };

    model model1 = model();

    model1.rUnit.genVAO();
    model1.rUnit.bindVAO();
    int attrib1 = model1.rUnit.loadToVAOf(vertices, 3, sizeof (vertices));
    int attrib2 = model1.rUnit.loadToVAOf(texCoords, 2, sizeof (texCoords));
    model1.rUnit.loadIndices(indices, sizeof (indices));
    model1.rUnit.activateAttribPointer(attrib1);
    model1.rUnit.activateAttribPointer(attrib2);

    //loading shaders, parsing them, linking them etc.
    shader ourShader("/home/sceptri/Dev/Dev/QtWorkspace/GameEngine/shaders/shader.vs",
                     "/home/sceptri/Dev/Dev/QtWorkspace/GameEngine/shaders/shader.fs"); //absolute path

    int tex1 = model1.genTexture("/home/sceptri/Dev/Dev/QtWorkspace/GameEngine/res/container.jpg", GL_RGB);
    int tex2 = model1.genTexture("/home/sceptri/Dev/Dev/QtWorkspace/GameEngine/res/awesomeface.png", GL_RGBA);

    model1.freeRender();

    camera cam = camera(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f));

    //Draw in wireframe mode?
    //yes
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    //no
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);


    //setting cursor to have a position callback to rotateCameraMouse from camera class
    setCursorPosCallback(window, &cam);

    //set scroll whell to have a callback, which calls changeFOV from camera class
    setScrollCallback(window, &cam);

    //set cursor to disappear, AKA FPS cursor
    setFPSCursor(window, true);

    while(!glfwWindowShouldClose(window))
    {
        //get current delta time
        getDeltaTime();

        //input
        if (processInput(window,GLFW_KEY_ESCAPE))
            closeWindow(window);

        if(processInput(window, GLFW_KEY_W))
            cam.translateCam(FORWARD);
        if(processInput(window, GLFW_KEY_S))
            cam.translateCam(BACKWARD);
        if(processInput(window, GLFW_KEY_A))
            cam.translateCam(LEFT);
        if(processInput(window, GLFW_KEY_D))
            cam.translateCam(RIGHT);

        //clearing window with color
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        model1.prepareRender();

        //shader
        ourShader.use();
        ourShader.setInt("Texture1", tex1);
        ourShader.setInt("Texture2", tex2);
        ourShader.setMat4("model", model1.modelMat);
        ourShader.setMat4("view", cam.getViewMat());
        ourShader.setMat4("projection", projectionMat(45.0f, 8/6, 0.1f, 100.0f, false));

        glClearError();
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
        glCheckError();

        glfwSwapBuffers(window);
        glfwPollEvents();

        model1.modelMat = glm::mat4();
    }

    model1.freeRender();
    model1.deleteModel(true);

    glfwTerminate();
    return 0;
}

