//
// Created by newst on 2022-07-18.
//

#ifndef BODA_BASEOBJECT_H
#define BODA_BASEOBJECT_H

#include <vector>

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

struct Index {
    unsigned int data[3];
    Index() = default;
    Index(unsigned int d1, unsigned int d2, unsigned int d3) {
        data[0] = d1;
        data[1] = d2;
        data[2] = d3;
    }
};

struct Mesh {
    float local[16] = {0};
    std::vector<Position> positions;
    std::vector<Index> indices;
    std::vector<Mesh> children;
};

class BaseObject {
public:
    virtual void setupGraphic(int width, int height) = 0;
    virtual void renderFrame(void* array = nullptr) = 0;

    ObjectType getType() const {
        return objectType;
    };
protected:
    unsigned int program = 0;
    ObjectType objectType = ObjectType::UNKNOWN;
};


#endif //BODA_BASEOBJECT_H
