cmake_minimum_required(VERSION 3.10.2)

project("nativelib")

add_library(${PROJECT_NAME}
             SHARED
             Light.cpp
             nativelib.cpp
             MainScene.cpp
             MLDelegate.cpp
             object/PlaneObject.cpp
             object/BoxObject.cpp
             object/ObjectFileLoader.cpp
             caculator/DetectionCalculator.cpp)

set( PROJECT_ROOT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../../../ )
set( THIRD_PARTY_PATH  ${PROJECT_ROOT_PATH}/thirdparty )
set( JNI_LIBS ${CMAKE_CURRENT_SOURCE_DIR}/../jniLibs)
set( THIRDPARTY_LIBRARY
        ${JNI_LIBS}/${ANDROID_ABI}/libtensorflowlite.so
        ${JNI_LIBS}/${ANDROID_ABI}/libtensorflowlite_gpu_delegate.so
        ${JNI_LIBS}/${ANDROID_ABI}/libnnapi_delegate_no_nnapi_implementation.so
        ${JNI_LIBS}/${ANDROID_ABI}/libnnapi_implementation.so
        ${JNI_LIBS}/${ANDROID_ABI}/libnnapi_util.so
        ${JNI_LIBS}/${ANDROID_ABI}/libNative_Noon.so )

target_include_directories(${PROJECT_NAME} PUBLIC
                            ${CMAKE_CURRENT_SOURCE_DIR}/include
                            ${CMAKE_CURRENT_SOURCE_DIR}/object/include
                            ${CMAKE_CURRENT_SOURCE_DIR}/caculator/include
                            ${THIRD_PARTY_PATH}/glm/
                            ${THIRD_PARTY_PATH}/Noon/src/include
                            ${THIRD_PARTY_PATH}/Noon/src/include/flatbuffers
                            ${THIRD_PARTY_PATH}/Noon/thirdparty/tensorflow)

find_library( log-lib
                log
                android-lib
                android)

target_link_libraries(${PROJECT_NAME} PUBLIC
                        GLESv3
                        EGL
                        android
                        ${log-lib}
                        ${android-lib}
                        ${THIRDPARTY_LIBRARY})
