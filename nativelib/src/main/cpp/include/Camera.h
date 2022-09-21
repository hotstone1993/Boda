//
// Created by newst on 2022-09-18.
//

#ifndef BODA_CAMERA_H
#define BODA_CAMERA_H

#include <unordered_map>
#include <string>

#include <GLES3/gl3.h>
#include <GLES3/gl3ext.h>
#include "glm/glm.hpp"
#include "glm/ext.hpp"

class Camera {
public:
    Camera(): position(0.0f, 0.0f, 0.0f),
            look(0.0f, 0.0f, -1.0f),
            up(0.0f, 1.0f, 0.0f)
            {
    };
    ~Camera() = default;

    void setupCamera(int width, int height) {
        if (width < height) {
            projectionMatrix = glm::perspectiveFov<float>(45, width, height, 0.1f, 100);
        } else {
            projectionMatrix = glm::perspectiveFov<float>(45, height, width, 0.1f, 100);
        }
        viewMatrix = glm::lookAt(position, look, up);
    }

    void setUniformBuffer(unsigned int program, unsigned int blockIndex) {
        glUniformBlockBinding(program, blockIndex, 0);
    }

    void createUniformBuffer() {
        glGenBuffers(1, &uboMatrices);

        glBindBuffer(GL_UNIFORM_BUFFER, uboMatrices);
        glBufferData(GL_UNIFORM_BUFFER, 2 * sizeof(glm::mat4), NULL, GL_STATIC_DRAW);
        glBindBuffer(GL_UNIFORM_BUFFER, 0);

        glBindBufferRange(GL_UNIFORM_BUFFER, 0, uboMatrices, 0, 2 * sizeof(glm::mat4));

        glBindBuffer(GL_UNIFORM_BUFFER, uboMatrices);
        glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::mat4), glm::value_ptr(projectionMatrix));
        glBindBuffer(GL_UNIFORM_BUFFER, 0);

        glBindBuffer(GL_UNIFORM_BUFFER, uboMatrices);
        glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::mat4), sizeof(glm::mat4), glm::value_ptr(viewMatrix));
        glBindBuffer(GL_UNIFORM_BUFFER, 0);
    }

    void setCameraPositionLocation(const size_t& key, unsigned int location) {
        cameraPositionLocation[key] = location;
    }

    void setCameraMatrix(const size_t& key) {
        auto item = cameraPositionLocation.find(key);
        if (item != cameraPositionLocation.end()) {
            glUniform3fv(item->second, 1, glm::value_ptr(position));
        }
    }

private:
    unsigned int uboMatrices;
    std::unordered_map<size_t, unsigned int> cameraPositionLocation;

    glm::mat4 viewMatrix{};
    glm::mat4 projectionMatrix{};

    glm::vec3 position;
    glm::vec3 look;
    glm::vec3 up;
};

#endif //BODA_CAMERA_H
