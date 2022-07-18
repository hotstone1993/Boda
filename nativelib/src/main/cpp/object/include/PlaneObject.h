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

    virtual void setupGraphic(unsigned int program) override;
    virtual void renderFrame(unsigned char* array = nullptr) override;
private:
    unsigned int loadSimpleTexture(unsigned char* array);

    unsigned int vertexLocation;
    unsigned int textureCoordinateLocation;

    unsigned short indices[6];
    float vertices[12];
    float textureCoordinates[8];

    const char* glVertexShader =
            "attribute vec4 vertexPosition;\n"
            "attribute vec2 attributeTextureCoordinate;\n"
            "varying vec3 fragColour;\n"
            "varying vec2 textureCord;\n"
            "void main()\n"
            "{\n"
            "    gl_Position = vertexPosition;\n"
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
