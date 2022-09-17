//
// Created by newst on 2022-07-18.
//

#ifndef BODA_PLANEOBJECT_H
#define BODA_PLANEOBJECT_H

#include "BaseObject.h"

class PlaneObject: public BaseObject {
public:
    PlaneObject(unsigned int idx);
    ~PlaneObject();

    virtual void setupGraphic(int width, int height, std::shared_ptr<Camera>& camera, AAssetManager *mgr) override;
    virtual void renderFrame(void* array) override;
private:
    unsigned int loadSimpleTexture(unsigned char* array);
    unsigned int vertexShader = 0;
    unsigned int fragmentShader = 0;
    unsigned int vertexLocation = 0;
    unsigned int textureCoordinateLocation = 0;
    unsigned int worldLocation;

    glm::mat4 worldMatrix{1};
    unsigned short indices[6];
    float vertices[12];
    float textureCoordinates[8];

    const char* glVertexShader =
            "attribute vec4 vertexPosition;\n"
            "attribute vec2 attributeTextureCoordinate;\n"
            "varying vec2 textureCord;\n"
            "uniform mat4 projection;\n"
            "uniform mat4 view;\n"
            "uniform mat4 world;\n"
            "void main()\n"
            "{\n"
            "    gl_Position = projection * view * world * vertexPosition;\n"
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
