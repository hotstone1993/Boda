//
// Created by newst on 2022-09-18.
//

#ifndef BODA_CAMERA_H
#define BODA_CAMERA_H

#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include "glm/glm.hpp"
#include "glm/ext.hpp"

class Camera {
public:
    Camera(): position(0.0f, 0.0f, 0.0f),
            look(0.0f, 0.0f, -1.0f),
            up(0.0f, 1.0f, 0.0f)
            {
        viewMatrix = glm::lookAt(position, look, up);
    };
    ~Camera() = default;

    void setupCamera(int width, int height) {
        if (width < height) {
            projectionMatrix = glm::perspectiveFov<float>(45, width, height, 0.1f, 100);
        } else {
            projectionMatrix = glm::perspectiveFov<float>(45, height, width, 0.1f, 100);
        }
    }

    void setProjectionLocation(unsigned int location) {
        projectionLocation.push_back(location);
    }

    void setViewLocation(unsigned int location) {
        viewLocation.push_back(location);
    }

    void setCameraMatrix(unsigned int idx) {
        glUniformMatrix4fv(projectionLocation[idx], 1, GL_FALSE, glm::value_ptr(projectionMatrix));
        glUniformMatrix4fv(viewLocation[idx], 1, GL_FALSE, glm::value_ptr(viewMatrix));
    }

private:
    std::vector<unsigned int> viewLocation;
    std::vector<unsigned int> projectionLocation;

    glm::mat4 viewMatrix{};
    glm::mat4 projectionMatrix{};

    glm::vec3 position;
    glm::vec3 look;
    glm::vec3 up;
};

#endif //BODA_CAMERA_H
