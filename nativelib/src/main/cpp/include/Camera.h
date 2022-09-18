//
// Created by newst on 2022-09-18.
//

#ifndef BODA_CAMERA_H
#define BODA_CAMERA_H

#include <unordered_map>
#include <string>

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

    void setProjectionLocation(const size_t& key, unsigned int location) {
        projectionLocation[key] = location;
    }

    void setViewLocation(const size_t& key, unsigned int location) {
        viewLocation[key] = location;
    }

    void setCameraPositionLocation(const size_t& key, unsigned int location) {
        cameraPositionLocation[key] = location;
    }

    void setCameraMatrix(const size_t& key) {
        glUniformMatrix4fv(projectionLocation[key], 1, GL_FALSE, glm::value_ptr(projectionMatrix));
        glUniformMatrix4fv(viewLocation[key], 1, GL_FALSE, glm::value_ptr(viewMatrix));

        glUniform3fv(cameraPositionLocation[key], 1, glm::value_ptr(position));
    }

private:
    std::unordered_map<size_t, unsigned int> cameraPositionLocation;
    std::unordered_map<size_t, unsigned int> viewLocation;
    std::unordered_map<size_t, unsigned int> projectionLocation;

    glm::mat4 viewMatrix{};
    glm::mat4 projectionMatrix{};

    glm::vec3 position;
    glm::vec3 look;
    glm::vec3 up;
};

#endif //BODA_CAMERA_H
