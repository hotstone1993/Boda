#include <jni.h>
#include "include/MainScene.h"

const char* const INSTANCE = "nativeInstance";

extern "C"
JNIEXPORT void JNICALL
Java_com_newstone_nativelib_NativeLib_init(JNIEnv* env, jclass clazz, jint w, jint h)
{
    MainScene* mainScene = new MainScene();

    jfieldID instanceId = env->GetStaticFieldID(clazz, INSTANCE, "J");
    env->SetStaticLongField(clazz, instanceId, reinterpret_cast<jlong>(mainScene));

    mainScene->setupGraphic(w, h);
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