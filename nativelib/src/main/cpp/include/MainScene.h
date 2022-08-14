//
// Created by newst on 2022-07-17.
//

#ifndef BODA_MAINSCENE_H
#define BODA_MAINSCENE_H

#include "list"
#include "MLDelegate.h"

class BaseObject;

class MainScene {
public:
    MainScene();
    ~MainScene();

    bool setupGraphic(int width, int height, const char* model, size_t modelSize);
    void renderFrame(unsigned char* image);

private:
    std::list<std::unique_ptr<BaseObject>> objects;
    MLDelegate mlDelegate;
};

#endif //BODA_MAINSCENE_H
