/*
 *
 * Revise the code I have written on 15th of october and earlier and maybe rework some parts
 *
 * ADD NOTES:
 *  add explanation in camera.cpp for reverse mouse movement
 *
*/

#include "engine.h"

//default value for width and height
int base_width = 800;
int base_height = 600;

float deltaTime = 0;
float lastTime = 0;


int main()
{

    GLFWwindow* window;
    if(Engine::createDisplay(&window, &base_width, &base_height, &lastTime, &deltaTime) < 0)
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

    Engine::model model1 = Engine::model();

    model1.rUnit.genVAO();
    model1.rUnit.bindVAO();
    int attrib1 = model1.rUnit.loadToVAOf(vertices, 3, sizeof (vertices));
    int attrib2 = model1.rUnit.loadToVAOf(texCoords, 2, sizeof (texCoords));
    model1.rUnit.loadIndices(indices, sizeof (indices));
    model1.rUnit.activateAttribPointer(attrib1);
    model1.rUnit.activateAttribPointer(attrib2);

    //loading shaders, parsing them, linking them etc.
    Engine::shader ourShader("/home/sceptri/Dev/Dev/QtWorkspace/GameEngine/Tester/shaders/shader.vs",
                     "/home/sceptri/Dev/Dev/QtWorkspace/GameEngine/Tester/shaders/shader.fs"); //absolute path

    int tex1 = model1.genTexture("/home/sceptri/Dev/Dev/QtWorkspace/GameEngine/Tester/res/container.jpg", GL_RGB);
    int tex2 = model1.genTexture("/home/sceptri/Dev/Dev/QtWorkspace/GameEngine/Tester/res/awesomeface.png", GL_RGBA);

    model1.freeRender();

    Engine::camera cam = Engine::camera(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f));

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
    Engine::setFPSCursor(window, true);

    while(!glfwWindowShouldClose(window))
    {
        //get current delta time
        Engine::getDeltaTime();

        //input
        if (Engine::processInput(window,GLFW_KEY_ESCAPE))
            Engine::closeWindow(window);

        if(Engine::processInput(window, GLFW_KEY_W))
            cam.translateCam(Engine::FORWARD);
        if(Engine::processInput(window, GLFW_KEY_S))
            cam.translateCam(Engine::BACKWARD);
        if(Engine::processInput(window, GLFW_KEY_A))
            cam.translateCam(Engine::LEFT);
        if(Engine::processInput(window, GLFW_KEY_D))
            cam.translateCam(Engine::RIGHT);

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
        ourShader.setMat4("projection", Engine::projectionMat(cam.getFOV(), base_width/base_height, 0.1f, 100.0f, false));

        Engine::glClearError();
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
        Engine::glCheckError();

        glfwSwapBuffers(window);
        glfwPollEvents();

        model1.modelMat = glm::mat4();
    }

    model1.freeRender();
    model1.deleteModel(true);

    glfwTerminate();
    return 0;
}

