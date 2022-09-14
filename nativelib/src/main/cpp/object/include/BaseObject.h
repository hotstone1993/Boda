//
// Created by newst on 2022-07-18.
//

#ifndef BODA_BASEOBJECT_H
#define BODA_BASEOBJECT_H

#include <vector>
#include "BaseMesh.h"
#include "GLUtils.h"

enum class ObjectType {
    UNKNOWN, BOX, PLANE
};


class BaseObject {
public:
    BaseObject() = default;
    virtual ~BaseObject() = default;

    virtual void setupGraphic(int width, int height, AAssetManager *mgr) = 0;
    virtual void renderFrame(void* array = nullptr) = 0;

    ObjectType getType() const {
        return objectType;
    };
protected:
    unsigned int program = 0;
    ObjectType objectType = ObjectType::UNKNOWN;
};


#endif //BODA_BASEOBJECT_H
