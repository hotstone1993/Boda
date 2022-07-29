//
// Created by newst on 2022-07-28.
//

#include "include/MLDelegate.h"


MLDelegate::MLDelegate(): ml(std::make_unique<Noon>()) {
}

MLDelegate::~MLDelegate() {
    ml->deinit();
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
        outputs.emplace_back(std::make_unique<float[]>(ml->getOutputBufferSize(idx)));
    }
}

void MLDelegate::process(const unsigned char* array) {
    for (size_t idx = 0; idx < pixelStride * height * width; ++idx) {
        tempBuffer[idx] = (array[idx] / 256.f) - 0.5f;
    }

    ml->inference(tempBuffer.get());

    for (int idx = 0; idx < outputs.size(); ++idx) {
        ml->getOutput(idx, outputs[idx].get());
    }
}

