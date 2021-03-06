//
// Created by newst on 2022-07-17.
//

#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <memory>

#include "include/MainScene.h"
#include "object/include/BaseObject.h"
#include "object/include/PlaneObject.h"
#include "object/include/BoxObject.h"

MainScene::MainScene() {
    objects.push_back(std::make_unique<PlaneObject>());
    objects.push_back(std::make_unique<BoxObject>());
}

MainScene::~MainScene() {

}

bool MainScene::setupGraphic(int width, int height) {
    for (const std::unique_ptr<BaseObject>& object: objects) {
        object->setupGraphic(width, height);
    }
    glEnable(GL_DEPTH_TEST);
    glViewport(0, 0, width, height);

    return true;
}

void MainScene::renderFrame(unsigned char* array)
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

    for (const std::unique_ptr<BaseObject>& object: objects) {
        object->renderFrame(array);
    }
}