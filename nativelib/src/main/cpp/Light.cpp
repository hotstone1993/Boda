//
// Created by newst on 2022-09-15.
//

#include "Light.h"

#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

Light::Light(float x, float y, float z) : position(x, y, z) {
}

void Light::setCameraPositionLocation(const size_t &key, unsigned int location) {
    lightPositionLocation[key] = location;
}

void Light::placeLight() {
}