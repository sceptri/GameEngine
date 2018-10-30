#include "camera.h"

namespace Engine
{
    extern int * base_width;
    extern int * base_height;

    extern float * deltaTime;

    camera::camera()
    {
        lastX = *base_width/2;
        lastY = *base_height/2;

        camFace = glm::vec3(0, 0, -1);

        calcRotFromCamFace();
    }

    camera::camera(glm::vec3 pos, glm::vec3 face, glm::vec3 upDir)
    {
        camPos = pos;
        camFace = face;
        camUp = upDir;

        calcRotFromCamFace();

        lastX = *base_width/2;
        lastY = *base_height/2;
    }

    camera::camera(glm::vec3 pos, double pitch, double yaw, glm::vec3 upDir)
    {
        camPos = pos;

        this->yaw = yaw;
        this->pitch = pitch;

        calcCamFaceFromRot();

        camUp = upDir;

        lastX = *base_width/2;
        lastY = *base_height/2;
    }

    glm::mat4 camera::getViewMat()
    {
        return glm::lookAt(camPos, camPos + camFace, camUp);
        //first is shift(pos) of new axises origin in terms of global coords
        //second is pos of the the target camera is facing in the global coords
        //third is up direction for the new axises
    }

    float camera::getFOV() const
    {
        return fov;
    }

    void camera::rotateCameraMouse(double xpos, double ypos)
    {
        if(firstMouse)
        {
            lastX = xpos;
            lastY = ypos;
            firstMouse = false;
        }

        double xoffset = xpos - lastX;
        double yoffset = lastY - ypos; //because otherwise mousemovement is inversed -- add explanation
        lastX = xpos;
        lastY = ypos;

        xoffset *= double(sensitivity);
        yoffset *= double(sensitivity);

        yaw += xoffset;
        pitch += yoffset;

        //gimball -- lock to prevent turning camera upside down etc
        if(pitch > 89.0)
            pitch = 89.0;
        if(pitch < -89.0)
            pitch = -89.0;

        calcCamFaceFromRot();
    }

    void camera::changeFOVScroll(double xoffset, double yoffset)
    {
        if(fov >= 1.0f && fov <= 45.0f)
            fov -= yoffset;
        if(fov <= 1.0f)
            fov = 1.0f;
        if(fov >= 45.0f)
            fov = 45.0f;
    }

    void camera::translateCam(int direction)
    {
        switch (direction)
        {
            case FORWARD:
            {
                camPos += camTranslateSpeed * camFace * *deltaTime;
                break;
            }
            case BACKWARD:
            {
                camPos -= camTranslateSpeed * camFace * *deltaTime;
                break;
            }
            case LEFT:
            {
                camPos -= glm::normalize(glm::cross(camFace, camUp)) * camTranslateSpeed * *deltaTime;
                break;
            }
            case RIGHT:
            {
                camPos += glm::normalize(glm::cross(camFace, camUp)) * camTranslateSpeed * *deltaTime;
                break;
            }
            default:
            {
                std::cout << "[ERROR]::WRONG_INPUT_FOR_CAMERA_TRANSLATION" <<std::endl;
            }
        }
    }

    void camera::calcCamFaceFromRot()
    {
        //more in explanation of camFace and in picture

        camFace.x = float(cos(glm::radians(yaw)) * cos(glm::radians(pitch)));
        camFace.y = float(sin(glm::radians(pitch)));
        camFace.z = float(sin(glm::radians(yaw)) * cos(glm::radians(pitch)));
        camFace = glm::normalize(camFace);
    }

    void camera::calcRotFromCamFace()
    {
        pitch = asin(double(camFace.y)) * (180/PI);
        yaw = asin(double(camFace.z) / cos(glm::radians(pitch))) * (180/PI);
    }
}
