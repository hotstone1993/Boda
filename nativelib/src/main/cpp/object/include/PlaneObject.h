//
// Created by newst on 2022-07-18.
//

#ifndef BODA_PLANEOBJECT_H
#define BODA_PLANEOBJECT_H

#include "BaseObject.h"

class PlaneObject: public BaseObject {
public:
    PlaneObject();
    ~PlaneObject();

    virtual void setupGraphic(int width, int height) override;
    virtual void renderFrame(unsigned char* array = nullptr) override;
private:
    unsigned int loadSimpleTexture(unsigned char* array);
    unsigned int vertexShader = 0;
    unsigned int fragmentShader = 0;
    unsigned int vertexLocation = 0;
    unsigned int textureCoordinateLocation = 0;
    unsigned int projectionLocation;
    unsigned int modelViewLocation;

    float projectionMatrix[16];
    float modelViewMatrix[16];
    unsigned short indices[6];
    float vertices[12];
    float textureCoordinates[8];

    const char* glVertexShader =
            "attribute vec4 vertexPosition;\n"
            "attribute vec2 attributeTextureCoordinate;\n"
            "varying vec2 textureCord;\n"
            "uniform mat4 projection;\n"
            "uniform mat4 modelView;\n"
            "void main()\n"
            "{\n"
            "    gl_Position = projection * modelView * vertexPosition;\n"
            "    textureCord = attributeTextureCoordinate;\n"
            "}\n";

    const char* glFragmentShader =
            "precision mediump float;\n"
            "uniform sampler2D texture;\n"
            "varying vec2 textureCord;\n"
            "void main()\n"
            "{\n"
            "    gl_FragColor = texture2D(texture, textureCord);\n"
            "}\n";
};


#endif //BODA_PLANEOBJECT_H
