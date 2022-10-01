#include <jni.h>
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>
#include "include/MainScene.h"

const char* const INSTANCE = "nativeInstance";

extern "C"
JNIEXPORT void JNICALL
Java_com_newstone_nativelib_NativeLib_init(JNIEnv* env, jclass clazz, jint w, jint h, jobject assetManager)
{
    AAssetManager* mgr = AAssetManager_fromJava(env, assetManager);
    MainScene* mainScene = new MainScene();

    jfieldID instanceId = env->GetStaticFieldID(clazz, INSTANCE, "J");
    env->SetStaticLongField(clazz, instanceId, reinterpret_cast<jlong>(mainScene));

    mainScene->setupGraphic(w, h, mgr);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_newstone_nativelib_NativeLib_step(JNIEnv* env, jclass clazz) {
    jfieldID instanceId = env->GetStaticFieldID(clazz, INSTANCE, "J");
    MainScene* mainScene = reinterpret_cast<MainScene *>(env->GetStaticLongField(clazz, instanceId));

    mainScene->renderFrame();
}


extern "C"
JNIEXPORT void JNICALL
Java_com_newstone_nativelib_NativeLib_setImage(JNIEnv *env, jclass clazz, jbyteArray input) {
    jbyte* inputBuffer = env->GetByteArrayElements(input, nullptr);

    jfieldID instanceId = env->GetStaticFieldID(clazz, INSTANCE, "J");
    MainScene* mainScene = reinterpret_cast<MainScene *>(env->GetStaticLongField(clazz, instanceId));

    mainScene->setImage(reinterpret_cast<unsigned char*>(inputBuffer));
    env->ReleaseByteArrayElements(input, inputBuffer, JNI_ABORT);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_newstone_nativelib_NativeLib_touch(JNIEnv *env, jclass clazz, jfloat x, jfloat y) {
    jfieldID instanceId = env->GetStaticFieldID(clazz, INSTANCE, "J");
    MainScene* mainScene = reinterpret_cast<MainScene *>(env->GetStaticLongField(clazz, instanceId));

    mainScene->touchEvent(x, y);
}