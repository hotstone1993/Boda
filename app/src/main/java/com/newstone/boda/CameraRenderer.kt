package com.newstone.boda

import android.content.res.AssetManager
import android.opengl.GLSurfaceView
import com.newstone.nativelib.NativeLib
import java.util.*
import javax.microedition.khronos.egl.EGLConfig
import javax.microedition.khronos.opengles.GL10

class CameraRenderer(val pixels: ByteArray, var listener: FPSEventListener, val asset: AssetManager): GLSurfaceView.Renderer {
    val timer = Timer()
    var count = 0L
    private val timerTask = object: TimerTask() {
        override fun run() {
            listener.handle(count.toString())
            count = 0
        }
    }

    override fun onSurfaceCreated(gl: GL10?, config: EGLConfig?) {
    }

    override fun onSurfaceChanged(gl: GL10?, width: Int, height: Int) {
        NativeLib.init(width, height, asset)
        timer.schedule(timerTask, 0, 1000)
    }

    override fun onDrawFrame(gl: GL10?) {
        count++
        NativeLib.step(pixels)
    }

    interface FPSEventListener {
        fun handle(fps: String)
    }
}
