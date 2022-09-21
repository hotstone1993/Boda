//
// Created by newst on 2022-07-17.
//

#include <GLES3/gl3.h>
#include <GLES3/gl3ext.h>
#include "include/MainScene.h"
#include "object/include/ObjectFactory.h"

MainScene::MainScene(): camera(std::make_shared<Camera>()) {
    initObjects();

    lights.push_back(std::make_unique<Light>(0.0f, 0.0f, 1.0f));
}

MainScene::~MainScene() {
}

void MainScene::initObjects() {
    std::hash<std::string> hasher;
    std::string base = "Object";
    int idx = 0;

    size_t curr = hasher(base + std::to_string(idx++));
    objects.push_back(ObjectFactory::createObject(ObjectType::PLANE, curr));

    curr = hasher(base + std::to_string(idx++));
    objects.push_back(ObjectFactory::createObject(ObjectType::BOX, curr));
}

bool MainScene::setupGraphic(int width, int height, AAssetManager *mgr) {
    mlDelegate.setup(mgr);

    camera->setupCamera(width, height);

    for (const std::unique_ptr<BaseObject>& object: objects) {
        object->setupGraphic(width, height, camera, mgr);
    }

    camera->createUniformBuffer();

    glEnable(GL_DEPTH_TEST);
    glViewport(0, 0, width, height);

    return true;
}

void MainScene::renderFrame(unsigned char* image) {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

    mlDelegate.setArray(image);

    for (const std::unique_ptr<Light>& light: lights) {
        light->placeLight();
    }

    for (const std::unique_ptr<BaseObject>& object: objects) {
        ObjectType type = object->getType();
        if (type == ObjectType::BOX) {
            object->renderFrame(mlDelegate.getOutput());
        } else if (type == ObjectType::PLANE) {
            object->renderFrame(image);
        }
    }
}