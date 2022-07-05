package com.newstone.boda

import android.opengl.GLSurfaceView
import javax.microedition.khronos.egl.EGL10
import javax.microedition.khronos.egl.EGLConfig
import javax.microedition.khronos.egl.EGLDisplay

class ConfigChooser: GLSurfaceView.EGLConfigChooser {
    protected var redSize = 5
    protected var greenSize = 6
    protected var blueSize = 5
    protected var alphaSize = 0
    protected var depthSize = 16
    protected var sampleSize = 4
    protected var stencilSize = 0

    override fun chooseConfig(egl: EGL10?, display: EGLDisplay?): EGLConfig? {
        val EGL_OPENGL_ES2_BIT = 4
        val configAttributes = intArrayOf(
            EGL10.EGL_RED_SIZE, redSize,
            EGL10.EGL_GREEN_SIZE, greenSize,
            EGL10.EGL_BLUE_SIZE, blueSize,
            EGL10.EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
            EGL10.EGL_SAMPLES, sampleSize,
            EGL10.EGL_DEPTH_SIZE, depthSize,
            EGL10.EGL_STENCIL_SIZE, stencilSize,
            EGL10.EGL_NONE
        )

        val num_config = IntArray(1)
        egl?.let { egl10 ->
            egl10.eglChooseConfig(display, configAttributes, null, 0, num_config)
            val numConfigs = num_config[0]
            val configs = arrayOfNulls<EGLConfig>(numConfigs)
            egl10.eglChooseConfig(display, configAttributes, configs, numConfigs, num_config)
            return configs[0]
        }
        return null
    }
}