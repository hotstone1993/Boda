//
// Created by newst on 2022-07-17.
//

#ifndef BODA_MAINSCENE_H
#define BODA_MAINSCENE_H

class MainScene {
public:
    MainScene();
    ~MainScene();
    bool setupGraphic(int width, int height);
    void renderFrame(unsigned char* array);

private:
    unsigned int loadShader(unsigned int shaderType, const char* shaderSource);
    unsigned int loadSimpleTexture(unsigned char* array);
    unsigned int createProgram(const char* vertexSource, const char * fragmentSource);

    unsigned int simpleCubeProgram;
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


#endif //BODA_MAINSCENE_H
