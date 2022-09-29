//
// Created by newst on 2022-07-18.
//

#ifndef BODA_PLANEOBJECT_H
#define BODA_PLANEOBJECT_H

#include "BaseObject.h"

class PlaneObject: public BaseObject {
public:
    PlaneObject(const size_t& key);
    ~PlaneObject();

    virtual void setupGraphic(int width, int height, std::shared_ptr<Camera>& camera, AAssetManager *mgr) override;
    virtual void renderFrame(void* array) override;
    virtual void touchEvent(float x, float y) override;
private:
    unsigned int loadSimpleTexture(unsigned char* array);
    unsigned int vertexShader = 0;
    unsigned int fragmentShader = 0;
    unsigned int vertexLocation = 0;
    unsigned int textureCoordinateLocation = 0;
    unsigned int worldLocation = 0;

    glm::mat4 worldMatrix{1};
    unsigned short indices[6];
    float vertices[12];
    float textureCoordinates[8];

    const char* glVertexShader =
            "#version 320 es\n"
            "in vec4 vertexPosition;\n"
            "in vec2 attributeTextureCoordinate;\n"
            "out vec2 textureCord;\n"
            "layout (std140) uniform Matrices\n"
            "{\n"
            "    mat4 projection;\n"
            "    mat4 view;\n"
            "};\n"
            "uniform mat4 world;\n"
            "void main()\n"
            "{\n"
            "    gl_Position = projection * view * world * vertexPosition;\n"
            "    textureCord = attributeTextureCoordinate;\n"
            "}\n";

    const char* glFragmentShader =
            "#version 320 es\n"
            "precision mediump float;\n"
            "uniform sampler2D image;\n"
            "in vec2 textureCord;\n"
            "out vec4 resultColor;\n"
            "void main()\n"
            "{\n"
            "    resultColor = texture(image, textureCord);\n"
            "}\n";
};


#endif //BODA_PLANEOBJECT_H
