
#ifndef BODA_BASEPARSER_H
#define BODA_BASEPARSER_H

#include <vector>
#include <iostream>
#include <fstream>
#include <string>

struct POSITION {
    float x, y, z;
    POSITION(float x, float y, float z) : x(x), y(y), z(z) {}
};

struct INDEX {
    unsigned int data[3];
    INDEX() = default;
    INDEX(float x, float y, float z) {
        data[0] = x;
        data[1] = y;
        data[2] = z;
    }
};

struct NORMAL {
    float x, y, z;
    NORMAL(float x, float y, float z) : x(x), y(y), z(z) {}
};

struct COORDINATE {
    float u, v;
    COORDINATE(float u, float v) : u(u), v(v) {}
};

struct Mesh {
    float mat[16] = { 0 };
    std::vector<POSITION> positions;
    std::vector<INDEX> indices;
    std::vector<NORMAL> normals;
    std::vector<COORDINATE> coordinates;
    std::vector<Mesh> children;
};


class BaseParser {
public:
    virtual bool createBSSFile(const char* filePath) = 0;

    void writeBaseInfo(const Mesh& m, std::ofstream& write) {
        write.write((char*)&m.mat, sizeof(float) * 16);
        unsigned int idxCount = m.indices.size();
        write.write((char*)&idxCount, sizeof(unsigned int));
        if (idxCount > 0)
            write.write((char*)m.indices.data(), sizeof(unsigned int) * idxCount * 3);

        unsigned int positionCount = m.positions.size();
        write.write((char*)&positionCount, sizeof(unsigned int));
        if (positionCount > 0)
            write.write((char*)m.positions.data(), sizeof(float) * positionCount * 3);

        unsigned int childrenCount = m.children.size();
        write.write((char*)&childrenCount, sizeof(unsigned int));

        for (const Mesh& child : m.children) {
            writeBaseInfo(child, write);
        }
    }

    bool writeBssFile(std::string filePath) {
        filePath += ".bss";

        std::ofstream write;
        write.open(filePath.c_str(), std::ios::out | std::ios::binary);

        if (write.fail() || write.bad()) {
            std::cout << "IO stream fail!\n";
            return false;
        }

        if (write.is_open()) {
            writeBaseInfo(root, write);
        }

        write.close();

        return true;
    }
protected:
    Mesh root;
};

#endif // BODA_BASEPARSER_H