//
// Created by newst on 2022-07-17.
//

#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <memory>

#include "include/MainScene.h"
#include "object/include/ObjectFactory.h"

MainScene::MainScene() {
    objects.push_back(ObjectFactory::createObject(ObjectType::PLANE));
    objects.push_back(ObjectFactory::createObject(ObjectType::BOX));
}

MainScene::~MainScene() {
}

bool MainScene::setupGraphic(int width, int height, const char* model, size_t modelSize) {
    mlDelegate.setup(model, modelSize);

    for (const std::unique_ptr<BaseObject>& object: objects) {
        object->setupGraphic(width, height);
    }
    glEnable(GL_DEPTH_TEST);
    glViewport(0, 0, width, height);

    return true;
}

void MainScene::renderFrame(unsigned char* image) {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

    mlDelegate.setArray(image);

    for (const std::unique_ptr<BaseObject>& object: objects) {
        ObjectType type = object->getType();
        if (type == ObjectType::BOX) {
            object->renderFrame(mlDelegate.getOutput());
        } else if (type == ObjectType::PLANE) {
            object->renderFrame(image);
        }
    }
}