/*
 *
 * Re-write class function using c_var notation for better readablity
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

bool model::renderPrepared = false;

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
    int at1 = model1.rUnit.loadToVAOf(vertices, 3, sizeof (vertices));
    int at2 = model1.rUnit.loadToVAOf(texCoords, 2, sizeof (texCoords));
    model1.rUnit.loadIndices(indices, sizeof (indices));
    model1.rUnit.activateAttribPointer(at1);
    model1.rUnit.activateAttribPointer(at2);

    //loading shaders, parsing them, linking them etc.
    shader ourShader("/home/sceptri/Dev/Dev/QtWorkspace/GameEngineOrdered/shaders/shader.vs",
                     "/home/sceptri/Dev/Dev/QtWorkspace/GameEngineOrdered/shaders/shader.fs"); //absolute path

    int tex1 = model1.genTexture("/home/sceptri/Dev/Dev/QtWorkspace/GameEngineOrdered/res/container.jpg", GL_RGB);
    int tex2 = model1.genTexture("/home/sceptri/Dev/Dev/QtWorkspace/GameEngineOrdered/res/awesomeface.png", GL_RGBA);

    model1.freeRender();

    //Draw in wireframe mode?
    //yes
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    //no
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    while(!glfwWindowShouldClose(window))
    {
        model1.rotate(glfwGetTime(), 0, 1, 0, true);
        model1.translate(2*glm::sin(glfwGetTime()), 0.0f, 0.0f);
        //input
        processInput(window, GLFW_KEY_ESCAPE, closeWindow);

        //clearing window with color
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        model1.prepareRender();

        //shader
        ourShader.use();
        ourShader.setInt("Texture1", tex1);
        ourShader.setInt("Texture2", tex2);
        ourShader.setMatrix("model", model1.modelMat);
        //view matrix is depedent on camera, which isn't set yet
        glm::mat4 view = glm::mat4();
        view = glm::translate(view, glm::vec3(0.0f, -0.5f, -4.5f));
        //view = glm::rotate(view, glm::radians(20.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        ourShader.setMatrix("view", view);
        ourShader.setMatrix("projection", projectionMat(45.0f, 8/6, 0.1f, 100.0f, false));

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

