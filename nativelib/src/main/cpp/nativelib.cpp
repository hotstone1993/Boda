#include <jni.h>
#include <android/log.h>

#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

#include <cstdio>
#include <cstdlib>
#include <cmath>

#include "Matrix.h"
#include <jni.h>
#include <jni.h>
#include <jni.h>
#include <jni.h>

#define LOG_TAG "libNative"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)


/* [vertexShader] */
static const char  glVertexShader[] =
        "attribute vec4 vertexPosition;\n"
        "attribute vec3 vertexColour;\n"
        "varying vec3 fragColour;\n"
        "void main()\n"
        "{\n"
        "    gl_Position = vertexPosition;\n"
        "    fragColour = vertexColour;\n"
        "}\n";
/* [vertexShader] */

/* [fragmentShader] */
static const char  glFragmentShader[] =
        "precision mediump float;\n"
        "varying vec3 fragColour;\n"
        "void main()\n"
        "{\n"
        "    gl_FragColor = vec4(fragColour, 1.0);\n"
        "}\n";
/* [fragmentShader] */

GLuint loadShader(GLenum shaderType, const char* shaderSource)
{
    GLuint shader = glCreateShader(shaderType);
    if (shader != 0)
    {
        glShaderSource(shader, 1, &shaderSource, NULL);
        glCompileShader(shader);
        GLint compiled = 0;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
        if (compiled != GL_TRUE)
        {
            GLint infoLen = 0;
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);

            if (infoLen > 0)
            {
                char * logBuffer = (char*) malloc(infoLen);

                if (logBuffer != NULL)
                {
                    glGetShaderInfoLog(shader, infoLen, NULL, logBuffer);
                    LOGE("Could not Compile Shader %d:\n%s\n", shaderType, logBuffer);
                    free(logBuffer);
                    logBuffer = NULL;
                }

                glDeleteShader(shader);
                shader = 0;
            }
        }
    }

    return shader;
}

GLuint createProgram(const char* vertexSource, const char * fragmentSource)
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
                char* logBuffer = (char*) malloc(bufLength);

                if (logBuffer != NULL)
                {
                    glGetProgramInfoLog(program, bufLength, NULL, logBuffer);
                    LOGE("Could not link program:\n%s\n", logBuffer);
                    free(logBuffer);
                    logBuffer = NULL;
                }
            }
            glDeleteProgram(program);
            program = 0;
        }
    }
    return program;
}

GLuint simpleCubeProgram;
GLuint vertexLocation;
GLuint vertexColourLocation;

/* [setupGraphics] */
bool setupGraphics(int width, int height)
{
    simpleCubeProgram = createProgram(glVertexShader, glFragmentShader);

    if (simpleCubeProgram == 0)
    {
        LOGE ("Could not create program");
        return false;
    }

    vertexLocation = glGetAttribLocation(simpleCubeProgram, "vertexPosition");
    vertexColourLocation = glGetAttribLocation(simpleCubeProgram, "vertexColour");

    glEnable(GL_DEPTH_TEST);

    glViewport(0, 0, width, height);

    return true;
}
/* [setupGraphics] */

/* [cubeVertices] */
GLfloat cubeVertices[] = {
                          -1.0f,  1.0f,  0.0f, /* Front. */
                          1.0f,  1.0f,  0.0f,
                          -1.0f, -1.0f,  0.0f,
                          1.0f, -1.0f,  0.0f
};
/* [cubeVertices] */
/* [colourComponents] */
GLfloat colour[] = {1.0f, 0.0f, 0.0f,
                    0.0f, 1.0f, 0.0f,
                    0.0f, 0.0f, 1.0f,
                    0.0f, 0.0f, 0.0f
};
/* [colourComponents] */

/* [indices] */
GLushort indices[] = {0, 2, 3, 0, 1, 3};
/* [indices] */

/* [renderFrame] */
void renderFrame()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

    glUseProgram(simpleCubeProgram);
    glVertexAttribPointer(vertexLocation, 3, GL_FLOAT, GL_FALSE, 0, cubeVertices);
    glEnableVertexAttribArray(vertexLocation);
    glVertexAttribPointer(vertexColourLocation, 3, GL_FLOAT, GL_FALSE, 0, colour);
    glEnableVertexAttribArray(vertexColourLocation);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, indices);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_newstone_nativelib_NativeLib_init(JNIEnv* env, jclass clazz, jint width, jint height)
{
    setupGraphics(width, height);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_newstone_nativelib_NativeLib_step(JNIEnv* env, jclass thiz) {
    renderFrame();
}