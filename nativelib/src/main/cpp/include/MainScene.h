//
// Created by newst on 2022-07-17.
//

#ifndef BODA_MAINSCENE_H
#define BODA_MAINSCENE_H

#include <list>
#include "MLDelegate.h"
#include "Light.h"

class BaseObject;

class MainScene {
public:
    MainScene();
    ~MainScene();

    bool setupGraphic(int width, int height, AAssetManager *mgr);
    void renderFrame(unsigned char* image);
private:
    std::list<std::unique_ptr<BaseObject>> objects;
    std::list<std::unique_ptr<Light>> lights;
    MLDelegate mlDelegate;
};

#endif //BODA_MAINSCENE_H
