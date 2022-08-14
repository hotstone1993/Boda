//
// Created by newst on 2022-07-28.
//

#include "include/MLDelegate.h"

MLDelegate::MLDelegate(): ml(std::make_unique<Noon>()),
                            thread(std::thread([&]() {
                                while (true) {
                                    if (BufferStatus::FINISH == status) {
                                        break;
                                    }

                                    {
                                        std::unique_lock<std::mutex> lk(mutex);
                                        cv.wait(lk, [&]() { return BufferStatus::READY == status;});
                                        ml->inference(tempBuffer.get());
                                    }
                                    for (int idx = 0; idx < outputs.size(); ++idx) {
                                        ml->getOutput(idx, outputs[idx].get());
                                    }
                                    status = BufferStatus::WAIT;
                                }
                            })) {
}

MLDelegate::~MLDelegate() {
    ml->deinit();
    status = BufferStatus::FINISH;
    cv.notify_all();
    thread.join();
}

void MLDelegate::setup(const char* model, size_t modelSize) {
    InferenceInfo info;
    info.type = IMAGE;
    info.input.shape = {width ,height, pixelStride};
    info.output = {};
    TFLInfo mlInfo;
    mlInfo.delegateType = GPU;
    mlInfo.numThread = 4;
    mlInfo.delegateType = false;

    ml->loadModel(model, modelSize, TENSORFLOW_LITE, mlInfo);
    ml->setup(info);

    tempBuffer = std::make_unique<float[]>(width * height * pixelStride);

    for (int idx = 0; idx < ml->getOutputArraySize(); ++idx) {
        size_t size = ml->getOutputBufferSize(idx);
        outputs.emplace_back(std::make_unique<float[]>(size));
    }
}

void MLDelegate::setArray(const unsigned char* array) {
    if (!mutex.try_lock())
        return;
    for (size_t idx = 0; idx < pixelStride * height * width; ++idx) {
        tempBuffer[idx] = (array[idx] / 256.f) - 0.5f;
    }
    status = BufferStatus::READY;
    mutex.unlock();
    cv.notify_one();
}

void* MLDelegate::getOutput() const {
    return outputs[1].get();
}