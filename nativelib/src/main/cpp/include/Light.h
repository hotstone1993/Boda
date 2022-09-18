//
// Created by newst on 2022-09-14.
//

#ifndef BODA_LIGHT_H
#define BODA_LIGHT_H

#include <unordered_map>

#include "glm/glm.hpp"
#include "glm/ext.hpp"

class Light {
public:
    Light() = default;
    Light(float x, float y, float z);
    virtual ~Light() = default;


    void setCameraPositionLocation(const size_t& key, unsigned int location);
    virtual void placeLight();

private:
    std::unordered_map<size_t, unsigned int> lightPositionLocation;
    glm::vec3 position;
};

#endif //BODA_LIGHT_H
