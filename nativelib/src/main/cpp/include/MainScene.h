//
// Created by newst on 2022-07-17.
//

#ifndef BODA_MAINSCENE_H
#define BODA_MAINSCENE_H

#include "list"

class BaseObject;

class MainScene {
public:
    MainScene();
    ~MainScene();

    bool setupGraphic(int width, int height);
    void renderFrame(unsigned char* array);

private:
    std::list<std::unique_ptr<BaseObject>> objects;
};


#endif //BODA_MAINSCENE_H
