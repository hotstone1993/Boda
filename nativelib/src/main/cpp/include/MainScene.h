//
// Created by newst on 2022-07-17.
//

#ifndef BODA_MAINSCENE_H
#define BODA_MAINSCENE_H

#include <unordered_map>
#include <list>
#include "MLDelegate.h"
#include "Light.h"

class BaseObject;
class Camera;

class MainScene {
public:
    MainScene();
    ~MainScene();

    bool setupGraphic(int width, int height, AAssetManager *mgr);
    void renderFrame();

    void setImage(unsigned char* image);
    void touchEvent(float x, float y);
private:
    void initObjects();

    std::list<std::unique_ptr<BaseObject>> objects;
    std::list<std::unique_ptr<Light>> lights;

    std::shared_ptr<Camera> camera;

    MLDelegate mlDelegate;
};

#endif //BODA_MAINSCENE_H
