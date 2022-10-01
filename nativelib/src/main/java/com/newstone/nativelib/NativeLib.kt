package com.newstone.nativelib

import android.content.res.AssetManager

class NativeLib {
    companion object {
        init {
            System.loadLibrary("nativelib")
        }
        @JvmStatic
        var nativeInstance: Long = 0L
        @JvmStatic
        external fun init(width: Int, height: Int, asset: AssetManager)
        @JvmStatic
        external fun step()
        @JvmStatic
        external fun setImage(input: ByteArray)
        @JvmStatic
        external fun touch(x: Float, y: Float)
    }
}