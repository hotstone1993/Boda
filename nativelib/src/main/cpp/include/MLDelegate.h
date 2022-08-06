//
// Created by newst on 2022-07-28.
//

#ifndef BODA_MLDELEGATE_H
#define BODA_MLDELEGATE_H

#include <memory>
#include <thread>

#include "Noon.h"

enum class BufferStatus {
    WAIT, READY, FINISH
};

class MLDelegate {
public:
    MLDelegate();
    ~MLDelegate();

    void setup(const char* model, size_t modelSize);
    void setArray(const unsigned char* array);
private:
    std::unique_ptr<Noon> ml;
    std::unique_ptr<float[]> tempBuffer;

    std::vector<std::unique_ptr<float[]>> outputs;
    std::thread thread;
    std::mutex mutex;
    BufferStatus status = BufferStatus::WAIT;

    // hardcoding
    int width = 630;
    int height = 480;
    int pixelStride = 4;
};


#endif //BODA_MLDELEGATE_H
