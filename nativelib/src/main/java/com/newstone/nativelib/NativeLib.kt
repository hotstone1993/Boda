package com.newstone.nativelib

class NativeLib {
    companion object {
        init {
            System.loadLibrary("nativelib")
        }
        @JvmStatic
        var nativeInstance: Long = 0L
        @JvmStatic
        external fun init(width: Int, height: Int, model: ByteArray)
        @JvmStatic
        external fun step(input: ByteArray)
    }
}