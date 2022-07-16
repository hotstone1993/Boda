cmake_minimum_required(VERSION 3.10.2)


project("nativelib")

add_library(nativelib
             SHARED
             nativelib.cpp
             MainScene.cpp
             Matrix.cpp)

target_include_directories(nativelib PUBLIC
                            ${CMAKE_CURRENT_SOURCE_DIR})

find_library( log-lib
              log )

target_link_libraries(nativelib
                        GLESv3
                        EGL
                        ${log-lib} )