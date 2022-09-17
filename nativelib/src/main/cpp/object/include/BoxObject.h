//
// Created by newst on 2022-07-19.
//

#ifndef BODA_BOXOBJECT_H
#define BODA_BOXOBJECT_H

#include "BaseObject.h"
#include "ObjectFileLoader.h"

class BoxObject : public BaseObject {
public:
    BoxObject(unsigned int idx);

    ~BoxObject();

    virtual void setupGraphic(int width, int height, std::shared_ptr<Camera>& camera, AAssetManager *mgr) override;

    virtual void renderFrame(void* array = nullptr) override;

private:
    void drawMesh(const BaseMesh& mesh);

    float angle = 0;
    std::unique_ptr<BaseLoader> loader;

    unsigned int vertexLocation{};
    unsigned int normalLocation{};
    unsigned int worldLocation{};

    unsigned int ambientLocation{};
    unsigned int diffuseLocation{};
    unsigned int specularLocation{};
    unsigned int alphaLocation{};
    unsigned int ksLocation{};

    BaseMesh root;
};


#endif //BODA_BOXOBJECT_H
