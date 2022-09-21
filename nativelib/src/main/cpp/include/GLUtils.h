//
// Created by newst on 2022-07-18.
//

#ifndef BODA_GLUTILS_H
#define BODA_GLUTILS_H

#include <GLES3/gl3.h>
#include <GLES3/gl3ext.h>
#include <memory>
#include <android/log.h>
#include <android/asset_manager.h>

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
                    LOGE("Shader Error: %s", logBuffer.get());

                    glDeleteShader(shader);
                    shader = 0;
                }
            }
        }

        return shader;
    }

    inline bool getAsset(AAssetManager *mgr, const char* filePath, size_t& fileSize, char* (&file)) {
        AAsset* asset = AAssetManager_open(mgr, filePath, AASSET_MODE_UNKNOWN);
        if (asset == nullptr) {
            return false;
        }

        fileSize = AAsset_getLength(asset);

        if (fileSize == 0){
            AAsset_close(asset);
            return false;
        }

        file = new char[fileSize];
        AAsset_read(asset, file, fileSize);

        return true;
    }
}

#endif //BODA_GLUTILS_H
