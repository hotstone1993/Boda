//
// Created by newst on 2022-08-16.
//

#include "include/ObjectFileLoader.h"
#include <charconv>
#include <fstream>
#include <sstream>

ObjectFileLoader::ObjectFileLoader() = default;

ObjectFileLoader::~ObjectFileLoader() = default;

void loadMesh(BaseMesh& mesh, std::ifstream& read) {
    read.read((char*)glm::value_ptr(mesh.local), sizeof(float) * 16);
    unsigned int indexSize = 0;
    unsigned int positionSize = 0;
    unsigned int normalSize = 0;
    unsigned int childrenSize = 0;
    read.read((char*)&indexSize, sizeof(unsigned int));
    mesh.indices.resize(indexSize);
    if (indexSize > 0) {
        read.read((char*)mesh.indices.data(), sizeof(float) * indexSize * 3);
    }

    read.read((char*)&positionSize, sizeof(unsigned int));
    mesh.positions.resize(positionSize);
    if (positionSize > 0) {
        read.read((char*)mesh.positions.data(), sizeof(float) * positionSize * 3);
    }

    read.read((char*)&normalSize, sizeof(unsigned int));
    mesh.normals.resize(normalSize);
    if (normalSize > 0) {
        read.read((char*)mesh.normals.data(), sizeof(float) * normalSize * 3);
    }

    read.read((char*)&childrenSize, sizeof(unsigned int));
    for (unsigned int idx = 0; idx < childrenSize; ++idx) {
        mesh.children.emplace_back();
        loadMesh(mesh.children.back(), read);
    }
}

bool ObjectFileLoader::loadFile(std::string_view path, BaseMesh& mesh) {
    std::ifstream read(path, std::ifstream::binary);

    if (read.is_open()) {
        loadMesh(mesh, read);
        read.close();
    }
    return true;
}