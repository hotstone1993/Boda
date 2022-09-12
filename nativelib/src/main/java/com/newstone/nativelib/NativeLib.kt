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
        external fun step(input: ByteArray)
    }
}