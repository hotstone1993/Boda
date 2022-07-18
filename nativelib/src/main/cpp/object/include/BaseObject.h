//
// Created by newst on 2022-07-18.
//

#ifndef BODA_BASEOBJECT_H
#define BODA_BASEOBJECT_H


class BaseObject {
public:
    virtual void setupGraphic(unsigned int program) = 0;
    virtual void renderFrame(unsigned char* array = nullptr) = 0;
};


#endif //BODA_BASEOBJECT_H
