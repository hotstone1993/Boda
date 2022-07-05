package com.newstone.boda

import android.opengl.GLSurfaceView
import com.newstone.nativelib.NativeLib
import javax.microedition.khronos.egl.EGLConfig
import javax.microedition.khronos.opengles.GL10

class CameraRenderer: GLSurfaceView.Renderer {
    override fun onSurfaceCreated(gl: GL10?, config: EGLConfig?) {
    }

    override fun onSurfaceChanged(gl: GL10?, width: Int, height: Int) {
        NativeLib.init(width, height)
    }

    override fun onDrawFrame(gl: GL10?) {
        NativeLib.step()
    }
}