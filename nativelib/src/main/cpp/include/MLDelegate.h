//
// Created by newst on 2022-07-28.
//

#ifndef BODA_MLDELEGATE_H
#define BODA_MLDELEGATE_H

#include <memory>

#include "Noon.h"

class MLDelegate {
public:
    MLDelegate();
    ~MLDelegate();

    void setup(const char* model, size_t modelSize);
    void process(const unsigned char* array);
private:
    std::unique_ptr<Noon> ml;
    std::unique_ptr<float[]> tempBuffer;

    // hardcoding
    int width = 630;
    int height = 480;
    int pixelStride = 4;
};


#endif //BODA_MLDELEGATE_H
