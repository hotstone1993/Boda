//
// Created by newst on 2022-09-14.
//

#ifndef BODA_LIGHT_H
#define BODA_LIGHT_H

#include "glm/glm.hpp"
#include "glm/ext.hpp"

class Light {
public:
    Light() = default;
    Light(float x, float y, float z);
    virtual ~Light() = default;

    virtual void placeLight();

    glm::vec3 position;
};

#endif //BODA_LIGHT_H
