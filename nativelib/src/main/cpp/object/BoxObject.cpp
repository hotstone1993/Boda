//
// Created by newst on 2022-07-19.
//
#include "Matrix.h"
#include "include/BoxObject.h"
#include "GLUtils.h"

BoxObject::BoxObject() {
    objectType = ObjectType::BOX;
    loader = std::make_unique<ObjectFileLoader>();
}

BoxObject::~BoxObject() {
    if (program != 0) {
        glDeleteProgram(program);
    }
}

void BoxObject::setupGraphic(int width, int height, const char* obj) {
    program = glCreateProgram();

    GLuint vertexShader = BODA::loadShader(GL_VERTEX_SHADER, glVertexShader);
    if (vertexShader == 0)
    {
        return;
    }

    GLuint fragmentShader = BODA::loadShader(GL_FRAGMENT_SHADER, glFragmentShader);
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
        }
    }

    vertexLocation = glGetAttribLocation(program, "vertexPosition");
    projectionLocation = glGetUniformLocation(program, "projection");
    modelViewLocation = glGetUniformLocation(program, "modelView");

    if (width < height) {
        matrixPerspective(projectionMatrix, 45, (float)width / (float)height, 0.1f, 100);
    } else {
        matrixPerspective(projectionMatrix, 45, (float)height / (float)width, 0.1f, 100);
    }

    loader->loadFile(obj, positions);
}

void BoxObject::renderFrame(void* array) {
    glUseProgram(program);

    matrixIdentityFunction(modelViewMatrix);

    matrixRotateX(modelViewMatrix, angle);
    matrixRotateY(modelViewMatrix, angle);

    matrixTranslate(modelViewMatrix, 0.0f, 0.0f, -50.0f);

    glVertexAttribPointer(vertexLocation, 3, GL_FLOAT, GL_FALSE, 0, positions.data());
    glEnableVertexAttribArray(vertexLocation);

    glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, projectionMatrix);
    glUniformMatrix4fv(modelViewLocation, 1, GL_FALSE, modelViewMatrix);

    glDrawArrays(GL_TRIANGLES, 0, positions.size());

    angle += 1;
    if (angle > 360)
    {
        angle -= 360;
    }
}