//
// Created by newst on 2022-07-18.
//

#ifndef BODA_GLUTILS_H
#define BODA_GLUTILS_H

#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <memory>
#include <android/log.h>

#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, "BODA", __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, "BODA", __VA_ARGS__)

namespace BODA {
    inline unsigned int loadShader(unsigned int shaderType, const char* shaderSource)
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
}

#endif //BODA_GLUTILS_H
