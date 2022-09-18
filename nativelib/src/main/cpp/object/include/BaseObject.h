//
// Created by newst on 2022-07-18.
//

#ifndef BODA_BASEOBJECT_H
#define BODA_BASEOBJECT_H

#include <vector>
#include "Camera.h"
#include "BaseMesh.h"
#include "GLUtils.h"

enum class ObjectType {
    UNKNOWN, BOX, PLANE
};

class BaseObject {
public:
    BaseObject(const size_t& key): key(key) {};
    virtual ~BaseObject() = default;

    virtual void setupGraphic(int width, int height, std::shared_ptr<Camera>& camera, AAssetManager *mgr) = 0;
    virtual void renderFrame(void* array = nullptr) = 0;

    ObjectType getType() const {
        return objectType;
    };
protected:
    unsigned int program = 0;
    size_t key;
    ObjectType objectType = ObjectType::UNKNOWN;

    std::unique_ptr<BaseMaterial> material;
    std::shared_ptr<Camera> camera;
};


#endif //BODA_BASEOBJECT_H
