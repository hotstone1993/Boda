//
// Created by newst on 2022-07-18.
//

#ifndef BODA_BASEOBJECT_H
#define BODA_BASEOBJECT_H


enum class ObjectType {
    UNKNOWN, BOX, PLANE
};

struct Position {
    float data[3];
    Position() = default;
    Position(float x, float y, float z) {
        data[0] = x;
        data[1] = y;
        data[2] = z;
    }
};

class BaseObject {
public:
    virtual void setupGraphic(int width, int height, const char* obj = nullptr) = 0;
    virtual void renderFrame(void* array = nullptr) = 0;

    ObjectType getType() const {
        return objectType;
    };
protected:
    unsigned int program = 0;
    ObjectType objectType = ObjectType::UNKNOWN;
};


#endif //BODA_BASEOBJECT_H
