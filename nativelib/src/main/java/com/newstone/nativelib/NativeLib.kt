package com.newstone.nativelib

class NativeLib {
    companion object {
        init {
            System.loadLibrary("nativelib")
        }
        @JvmStatic
        external fun init(width: Int, height: Int)
        @JvmStatic
        external fun step(input: ByteArray)
    }
}