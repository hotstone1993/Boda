//
// Created by newst on 2022-07-28.
//

#ifndef BODA_MLDELEGATE_H
#define BODA_MLDELEGATE_H

#include <memory>
#include <thread>
#include <condition_variable>

#include "Noon.h"

enum class BufferStatus {
    WAIT, READY, FINISH
};

class AAssetManager;

class MLDelegate {
public:
    MLDelegate();
    ~MLDelegate();

    void setup(AAssetManager *mgr);
    void setArray(const unsigned char* array);

    void* getOutput() const;
private:
    std::unique_ptr<Noon> ml;
    std::unique_ptr<float[]> tempBuffer;

    std::vector<std::unique_ptr<float[]>> outputs;
    std::thread thread;
    std::mutex mutex;
    std::condition_variable cv;
    BufferStatus status = BufferStatus::WAIT;

    // hardcoding
    int width = 630;
    int height = 480;
    int pixelStride = 4;
};


#endif //BODA_MLDELEGATE_H
