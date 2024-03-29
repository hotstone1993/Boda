//
// Created by newst on 2022-07-18.
//

#include "PlaneObject.h"
#include "GLUtils.h"

PlaneObject::PlaneObject(const size_t& key): BaseObject(key),
                            indices {0, 2, 3, 0, 3, 1},
                            vertices {
                                    -1.0f,  1.0f, 0.0f,
                                    1.0f,  1.0f, 0.0f,
                                    -1.0f, -1.0f, 0.0f,
                                    1.0f, -1.0f, 0.0f },
                            textureCoordinates {
                                    1.0f, 0.0f,
                                    1.0f, 1.0f,
                                    0.0f, 0.0f,
                                    0.0f, 1.0f,} {
    objectType = ObjectType::PLANE;
    position = glm::vec3(0.0f, 0.0f, -95.0f);
}

PlaneObject::~PlaneObject() {
    if (vertexShader == 0) {
        glDeleteShader(vertexShader);
    }
    if (fragmentShader == 0) {
        glDeleteShader(fragmentShader);
    }
    if (program != 0) {
        glDeleteProgram(program);
    }
}

void PlaneObject::setupGraphic(int width, int height, std::shared_ptr<Camera>& camera, AAssetManager *mgr) {
    program = glCreateProgram();
    this->camera = camera;

    imageSize = width * height * 3;
    imageBuffer = std::make_unique<unsigned char[]>(imageSize);

    vertexShader = BODA::loadShader(GL_VERTEX_SHADER, glVertexShader);
    if (vertexShader == 0)
    {
        return;
    }

    fragmentShader = BODA::loadShader(GL_FRAGMENT_SHADER, glFragmentShader);
    if (fragmentShader == 0)
    {
        return;
    }

    if (program != 0)
    {
        glAttachShader(program, vertexShader);
        glAttachShader(program, fragmentShader);
        glLinkProgram(program);
        glUseProgram(program);
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
                    glGetProgramInfoLog(program, bufLength, nullptr, logBuffer.get());
                    LOGE("Could not link program:\n%s\n", logBuffer.get());
                }
            }
            glDeleteProgram(program);
            program = 0;
            return;
        }
    }
    vertexLocation = glGetAttribLocation(program, "vertexPosition");
    textureCoordinateLocation = glGetAttribLocation(program, "attributeTextureCoordinate");
    unsigned int matrices = glGetUniformBlockIndex(program, "Matrices");
    camera->setUniformBuffer(program, matrices);
    worldLocation = glGetUniformLocation(program, "world");

    worldMatrix = glm::scale(worldMatrix, glm::vec3(48.f / (height / width * 2.f), 64 / (height / width * 2.f), 1));
    worldMatrix = glm::translate(worldMatrix, position);
}

void PlaneObject::touchEvent(float x, float y) {
    // Nothing
}

void PlaneObject::renderFrame(void* array) {
    if (program == 0)
        return;

    glUseProgram(program);
    glVertexAttribPointer(vertexLocation, 3, GL_FLOAT, GL_FALSE, 0, vertices);
    glEnableVertexAttribArray(vertexLocation);
    glVertexAttribPointer(textureCoordinateLocation, 2, GL_FLOAT, GL_FALSE, 0, textureCoordinates);
    glEnableVertexAttribArray(textureCoordinateLocation);

    camera->setCameraMatrix(key);

    glUniformMatrix4fv(worldLocation, 1, GL_FALSE, glm::value_ptr(worldMatrix));

    GLuint id = loadSimpleTexture(imageBuffer.get());

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, indices);

    glDeleteTextures(1, &id);
}

void PlaneObject::setImage(unsigned char* image) {
    memcpy(imageBuffer.get(), image, sizeof(unsigned char) * imageSize);
}

unsigned int PlaneObject::loadSimpleTexture(unsigned char* array)
{
    GLuint textureId;

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    glGenTextures(1, &textureId);

    glActiveTexture(GL_TEXTURE0);

    glBindTexture(GL_TEXTURE_2D, textureId);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 640, 480, 0, GL_RGBA, GL_UNSIGNED_BYTE, array);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    return textureId;
}