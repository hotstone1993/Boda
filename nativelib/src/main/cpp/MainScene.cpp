//
// Created by newst on 2022-07-17.
//

#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <memory>

#include "MainScene.h"

MainScene::MainScene(): indices {0, 2, 3, 0, 1, 3},
                        vertices {
                            -1.0f,  1.0f,  0.0f,
                            1.0f,  1.0f,  0.0f,
                            -1.0f, -1.0f,  0.0f,
                            1.0f, -1.0f,  0.0f },
                        textureCoordinates {
                            0.0f, 1.0f,
                            0.0f, 0.0f,
                            1.0f, 1.0f,
                            1.0f, 0.0f } {

}

MainScene::~MainScene() {

}

bool MainScene::setupGraphic(int width, int height) {
    simpleCubeProgram = createProgram(glVertexShader, glFragmentShader);

    if (simpleCubeProgram == 0)
    {
        return false;
    }

    vertexLocation = glGetAttribLocation(simpleCubeProgram, "vertexPosition");
    textureCoordinateLocation = glGetAttribLocation(simpleCubeProgram, "attributeTextureCoordinate");

    glEnable(GL_DEPTH_TEST);

    glViewport(0, 0, width, height);

    return true;
}

void MainScene::renderFrame(unsigned char* array)
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

    glUseProgram(simpleCubeProgram);
    glVertexAttribPointer(vertexLocation, 3, GL_FLOAT, GL_FALSE, 0, vertices);
    glEnableVertexAttribArray(vertexLocation);
    glVertexAttribPointer(textureCoordinateLocation, 2, GL_FLOAT, GL_FALSE, 0, textureCoordinates);
    glEnableVertexAttribArray(textureCoordinateLocation);

    loadSimpleTexture(array);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, indices);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

unsigned int MainScene::loadShader(unsigned int shaderType, const char* shaderSource)
{
    GLuint shader = glCreateShader(shaderType);
    if (shader != 0)
    {
        glShaderSource(shader, 1, &shaderSource, nullptr);
        glCompileShader(shader);
        GLint compiled = 0;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
        if (compiled != GL_TRUE)
        {
            GLint infoLen = 0;
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);

            if (infoLen > 0)
            {
                std::unique_ptr<char> logBuffer = std::make_unique<char>(infoLen);

                if (logBuffer != nullptr)
                {
                    glGetShaderInfoLog(shader, infoLen, nullptr, logBuffer.get());
                }

                glDeleteShader(shader);
                shader = 0;
            }
        }
    }

    return shader;
}

unsigned int MainScene::loadSimpleTexture(unsigned char* array)
{
    GLuint textureId;

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    glGenTextures(1, &textureId);

    glActiveTexture(GL_TEXTURE0);

    glBindTexture(GL_TEXTURE_2D, textureId);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 960, 540, 0, GL_RGBA, GL_UNSIGNED_BYTE, array);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    return textureId;
}

unsigned int MainScene::createProgram(const char* vertexSource, const char * fragmentSource)
{
    GLuint vertexShader = loadShader(GL_VERTEX_SHADER, vertexSource);
    if (vertexShader == 0)
    {
        return 0;
    }

    GLuint fragmentShader = loadShader(GL_FRAGMENT_SHADER, fragmentSource);
    if (fragmentShader == 0)
    {
        return 0;
    }

    GLuint program = glCreateProgram();

    if (program != 0)
    {
        glAttachShader(program, vertexShader);
        glAttachShader(program, fragmentShader);
        glLinkProgram(program);
        GLint linkStatus = GL_FALSE;
        glGetProgramiv(program, GL_LINK_STATUS, &linkStatus);
        if(linkStatus != GL_TRUE)
        {
            GLint bufLength = 0;
            glGetProgramiv(program, GL_INFO_LOG_LENGTH, &bufLength);
            if (bufLength > 0)
            {
                std::unique_ptr<char> logBuffer = std::make_unique<char>(bufLength);
                if (logBuffer != nullptr)
                {
                    glGetProgramInfoLog(program, bufLength, NULL, logBuffer.get());
                }
            }
            glDeleteProgram(program);
            program = 0;
        }
    }
    return program;
}