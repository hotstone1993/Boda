//
// Created by newst on 2022-09-14.
//

#ifndef BODA_BASEMESH_H
#define BODA_BASEMESH_H

#include "BaseMaterial.h"
#include <memory>

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

struct Normal {
    float data[3];
    Normal() = default;
    Normal(float d1, float d2, float d3) {
        data[0] = d1;
        data[1] = d2;
        data[2] = d3;
    }
};

class BaseMesh {
public:
    BaseMesh() = default;
    virtual ~BaseMesh() = default;

    glm::mat4 local;
    std::vector<Position> positions;
    std::vector<Index> indices;
    std::vector<Normal> normals;
    std::vector<BaseMesh> children;
};

#endif //BODA_BASEMESH_H
