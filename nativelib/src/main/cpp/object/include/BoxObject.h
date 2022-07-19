//
// Created by newst on 2022-07-19.
//

#ifndef BODA_BOXOBJECT_H
#define BODA_BOXOBJECT_H

#include "BaseObject.h"

class BoxObject : public BaseObject {
public:
    BoxObject();

    ~BoxObject();

    virtual void setupGraphic(int width, int height) override;

    virtual void renderFrame(unsigned char *array = nullptr) override;

private:
    float angle = 0;

    unsigned int vertexLocation;
    unsigned int colorLocation;
    unsigned int projectionLocation;
    unsigned int modelViewLocation;

    float projectionMatrix[16];
    float modelViewMatrix[16];
    unsigned short indices[36] = {0, 2, 3,
                                  0, 1, 3,
                                  4, 6, 7,
                                  4, 5, 7,
                                  8, 9, 10,
                                  11, 8, 10,
                                  12, 13, 14,
                                  15, 12, 14,
                                  16, 17, 18,
                                  16, 19, 18,
                                  20, 21, 22,
                                  20, 23, 22};
    float vertices[72] = {-1.0f, 1.0f, -1.0f, /* Back. */
                          1.0f, 1.0f, -1.0f,
                          -1.0f, -1.0f, -1.0f,
                          1.0f, -1.0f, -1.0f,
                          -1.0f, 1.0f, 1.0f, /* Front. */
                          1.0f, 1.0f, 1.0f,
                          -1.0f, -1.0f, 1.0f,
                          1.0f, -1.0f, 1.0f,
                          -1.0f, 1.0f, -1.0f, /* Left. */
                          -1.0f, -1.0f, -1.0f,
                          -1.0f, -1.0f, 1.0f,
                          -1.0f, 1.0f, 1.0f,
                          1.0f, 1.0f, -1.0f, /* Right. */
                          1.0f, -1.0f, -1.0f,
                          1.0f, -1.0f, 1.0f,
                          1.0f, 1.0f, 1.0f,
                          -1.0f, -1.0f, -1.0f, /* Top. */
                          -1.0f, -1.0f, 1.0f,
                          1.0f, -1.0f, 1.0f,
                          1.0f, -1.0f, -1.0f,
                          -1.0f, 1.0f, -1.0f, /* Bottom. */
                          -1.0f, 1.0f, 1.0f,
                          1.0f, 1.0f, 1.0f,
                          1.0f, 1.0f, -1.0f};
    float verticesColor[72] = {1.0f, 0.0f, 0.0f,
                                    1.0f, 0.0f, 0.0f,
                                    1.0f, 0.0f, 0.0f,
                                    1.0f, 0.0f, 0.0f,
                                    0.0f, 1.0f, 0.0f,
                                    0.0f, 1.0f, 0.0f,
                                    0.0f, 1.0f, 0.0f,
                                    0.0f, 1.0f, 0.0f,
                                    0.0f, 0.0f, 1.0f,
                                    0.0f, 0.0f, 1.0f,
                                    0.0f, 0.0f, 1.0f,
                                    0.0f, 0.0f, 1.0f,
                                    1.0f, 1.0f, 0.0f,
                                    1.0f, 1.0f, 0.0f,
                                    1.0f, 1.0f, 0.0f,
                                    1.0f, 1.0f, 0.0f,
                                    0.0f, 1.0f, 1.0f,
                                    0.0f, 1.0f, 1.0f,
                                    0.0f, 1.0f, 1.0f,
                                    0.0f, 1.0f, 1.0f,
                                    1.0f, 0.0f, 1.0f,
                                    1.0f, 0.0f, 1.0f,
                                    1.0f, 0.0f, 1.0f,
                                    1.0f, 0.0f, 1.0f
    };

    const char *glVertexShader =
            "attribute vec4 vertexPosition;\n"
            "attribute vec3 vertexColour;\n"
            "varying vec3 fragColour;\n"
            "uniform mat4 projection;\n"
            "uniform mat4 modelView;\n"
            "void main()\n"
            "{\n"
            "    gl_Position = projection * modelView * vertexPosition;\n"
            "    fragColour = vertexColour;\n"
            "}\n";

    const char *glFragmentShader =
            "precision mediump float;\n"
            "varying vec3 fragColour;\n"
            "void main()\n"
            "{\n"
            "    gl_FragColor = vec4(fragColour, 1.0);\n"
            "}\n";
};


#endif //BODA_BOXOBJECT_H
