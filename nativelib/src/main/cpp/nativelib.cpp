#include <jni.h>
#include "include/MainScene.h"

const char* const INSTANCE = "nativeInstance";

extern "C"
JNIEXPORT void JNICALL
Java_com_newstone_nativelib_NativeLib_init(JNIEnv* env, jclass clazz, jint w, jint h, jbyteArray m, jbyteArray obj)
{
    char* model = nullptr;
    char* object = nullptr;
    size_t modelSize = env->GetArrayLength(m);
    size_t objSize = env->GetArrayLength(obj);

    if (modelSize > 0) {
        model = new char[modelSize];
        jbyte* modelBuffer = env->GetByteArrayElements(m, nullptr);
        memcpy(model, modelBuffer, sizeof(char) * modelSize);
    }

    if (objSize > 0) {
        object = new char[objSize];
        jbyte* objBuffer = env->GetByteArrayElements(obj, nullptr);
        memcpy(object, objBuffer, sizeof(char) * objSize);
    }

    MainScene* mainScene = new MainScene();

    jfieldID instanceId = env->GetStaticFieldID(clazz, INSTANCE, "J");
    env->SetStaticLongField(clazz, instanceId, reinterpret_cast<jlong>(mainScene));

    mainScene->setupGraphic(w, h, reinterpret_cast<const char *>(model), modelSize, object);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_newstone_nativelib_NativeLib_step(JNIEnv* env, jclass clazz, jbyteArray input) {
    jbyte* inputBuffer = env->GetByteArrayElements(input, nullptr);

    jfieldID instanceId = env->GetStaticFieldID(clazz, INSTANCE, "J");
    MainScene* mainScene = reinterpret_cast<MainScene *>(env->GetStaticLongField(clazz, instanceId));

    mainScene->renderFrame(reinterpret_cast<unsigned char*>(inputBuffer));
    env->ReleaseByteArrayElements(input, inputBuffer, JNI_ABORT);
}