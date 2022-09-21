//
// Created by newst on 2022-09-15.
//

#include "Light.h"

#include <GLES3/gl3.h>
#include <GLES3/gl3ext.h>

Light::Light(float x, float y, float z) : position(x, y, z) {
}

void Light::setCameraPositionLocation(const size_t &key, unsigned int location) {
    lightPositionLocation[key] = location;
}

void Light::placeLight() {
}