//
// Created by newst on 2022-07-19.
//
#include "include/BoxObject.h"

BoxObject::BoxObject(const size_t& key): BaseObject(key) {
    objectType = ObjectType::BOX;
    loader = std::make_unique<ObjectFileLoader>();
    material = std::make_unique<BaseMaterial>();

    material->ambient = glm::vec3(0.2f, 0.2f, 0.2f);
    material->diffuse = glm::vec3(0.0f, 0.3f, 0.0f);
    material->specular = glm::vec3(0.6f, 0.6f, 0.6f);
    material->alpha = 9.0f;
    material->ks = 0.8f;
}

BoxObject::~BoxObject() {
    if (program != 0) {
        glDeleteProgram(program);
    }
}

void BoxObject::setupGraphic(int width, int height, std::shared_ptr<Camera>& camera, AAssetManager *mgr) {
    program = glCreateProgram();
    this->camera = camera;
    size_t shaderSize = 0;
    char* shader = nullptr;

    if (!BODA::getAsset(mgr, "shader/ObjectVertexShader.glsl", shaderSize, shader)) {
        return;
    }

    GLuint vertexShader = BODA::loadShader(GL_VERTEX_SHADER, shader);
    if (vertexShader == 0)
    {
        return;
    }
    delete shader;
    shader = nullptr;

    if (!BODA::getAsset(mgr, "shader/ObjectFragmentShader.glsl", shaderSize, shader)) {
        return;
    }

    GLuint fragmentShader = BODA::loadShader(GL_FRAGMENT_SHADER, shader);
    if (fragmentShader == 0)
    {
        return;
    }
    delete shader;
    shader = nullptr;

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
    normalLocation = glGetAttribLocation(program, "vertexNormal");
    unsigned int matrices = glGetUniformBlockIndex(program, "Matrices");
    camera->setUniformBuffer(program, matrices);
    worldLocation = glGetUniformLocation(program, "world");

    camera->setCameraPositionLocation(key, glGetUniformLocation(program, "cameraPosition"));
    ambientLocation = glGetUniformLocation(program, "ambient");
    diffuseLocation = glGetUniformLocation(program, "diffuse");
    specularLocation = glGetUniformLocation(program, "specular");
    alphaLocation = glGetUniformLocation(program, "alpha");
    ksLocation = glGetUniformLocation(program, "ks");

    loader->loadFile("/sdcard/Download/dragon.bss", root);
}

void BoxObject::renderFrame(void* array) {
    if (program == 0)
        return;

    glUseProgram(program);

    camera->setCameraMatrix(key);

    glUniform3fv(ambientLocation, 1, glm::value_ptr(material->ambient));
    glUniform3fv(diffuseLocation, 1, glm::value_ptr(material->diffuse));
    glUniform3fv(specularLocation, 1, glm::value_ptr(material->specular));
    glUniform1f(alphaLocation, material->alpha);
    glUniform1f(ksLocation, material->ks);

    drawMesh(root);
}


void BoxObject::drawMesh(const BaseMesh& mesh) {
    glm::mat resultLocalMatrix(mesh.local);
    resultLocalMatrix = glm::translate(resultLocalMatrix, glm::vec3(0.0f, 0.0f, -40.0f));
    static float degree = 0.f;
    degree += 0.005f;
    resultLocalMatrix = glm::rotate(resultLocalMatrix, glm::radians(degree), {1, 0, 0});
    resultLocalMatrix = glm::rotate(resultLocalMatrix, glm::radians(degree), {0, 1, 0});
    float scaleFactor = 0.2f;
    resultLocalMatrix = glm::scale(resultLocalMatrix, glm::vec3(scaleFactor, scaleFactor, scaleFactor));

    glVertexAttribPointer(vertexLocation, 3, GL_FLOAT, GL_FALSE, 0, mesh.positions.data());
    glEnableVertexAttribArray(vertexLocation);
    glVertexAttribPointer(normalLocation, 3, GL_FLOAT, GL_FALSE, 0, mesh.normals.data());
    glEnableVertexAttribArray(normalLocation);

    glUniformMatrix4fv(worldLocation, 1, GL_FALSE, glm::value_ptr(resultLocalMatrix));

    glDrawElements(GL_TRIANGLES, mesh.indices.size() * 3, GL_UNSIGNED_INT, mesh.indices.data());

    for (const BaseMesh& child: mesh.children) {
        drawMesh(child);
    }
}