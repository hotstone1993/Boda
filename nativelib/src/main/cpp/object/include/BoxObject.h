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

    virtual void setupGraphic(int width, int height) override;

    virtual void renderFrame(void* array = nullptr) override;

private:
    void drawMesh(const Mesh& mesh);

    float angle = 0;
    std::unique_ptr<BaseLoader> loader;

    unsigned int vertexLocation{};
    unsigned int projectionLocation{};
    unsigned int localLocation{};

    glm::mat4 projectionMatrix{};
    Mesh root;

    const char *glVertexShader =
            "attribute vec4 vertexPosition;\n"
            "uniform mat4 projection;\n"
            "uniform mat4 modelView;\n"
            "void main()\n"
            "{\n"
            "    gl_Position = projection * modelView * vertexPosition;\n"
            "}\n";

    const char *glFragmentShader =
            "precision mediump float;\n"
            "void main()\n"
            "{\n"
            "    gl_FragColor = vec4(0.3, 0.3, 0.3, 1.0);\n"
            "}\n";
};


#endif //BODA_BOXOBJECT_H
