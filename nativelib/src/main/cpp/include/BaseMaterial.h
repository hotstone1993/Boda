//
// Created by newst on 2022-09-14.
//

#ifndef BODA_BASEMATERIAL_H
#define BODA_BASEMATERIAL_H

#include "glm/glm.hpp"
#include "glm/ext.hpp"

class BaseMaterial {
public:
    BaseMaterial() = default;
    BaseMaterial(const BaseMaterial& other) {
        this->ambient = other.ambient;
        this->diffuse = other.diffuse;
        this->specular = other.specular;
    };
    virtual ~BaseMaterial() {};

    glm::vec3 ambient{0.f};
    glm::vec3 diffuse{0.f};
    glm::vec3 specular{0.f};
};

#endif //BODA_BASEMATERIAL_H
