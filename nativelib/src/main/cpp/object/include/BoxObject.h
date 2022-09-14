//
// Created by newst on 2022-07-19.
//

#ifndef BODA_BOXOBJECT_H
#define BODA_BOXOBJECT_H

#include "BaseObject.h"
#include "ObjectFileLoader.h"

class BoxObject : public BaseObject {
public:
    BoxObject();

    ~BoxObject();

    virtual void setupGraphic(int width, int height, AAssetManager *mgr) override;

    virtual void renderFrame(void* array = nullptr) override;

private:
    void drawMesh(const BaseMesh& mesh);

    float angle = 0;
    std::unique_ptr<BaseLoader> loader;

    unsigned int vertexLocation{};
    unsigned int normalLocation{};
    unsigned int projectionLocation{};
    unsigned int localLocation{};

    glm::mat4 projectionMatrix{};
    BaseMesh root;
};


#endif //BODA_BOXOBJECT_H
