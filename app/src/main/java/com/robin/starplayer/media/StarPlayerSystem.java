package com.robin.starplayer.media;

/**
 * Created by robin on 2017/9/15.
 */

public class StarPlayerSystem {
    public static final String EXTERN_PATH = "com.robin.starplayer.media.PATH";

    static{
        System.loadLibrary("starplayer");
        System.loadLibrary("avdevice-57");
        System.loadLibrary("avfilter-6");
        System.loadLibrary("avformat-57");
        System.loadLibrary("avutil-55");
        System.loadLibrary("postproc-54");
        System.loadLibrary("swresample-2");
        System.loadLibrary("swscale-4");
        System.loadLibrary("avcodec-57");
        System.loadLibrary("avresample-3");
    }

    public static native int version();

    public static native String cofiguration();

    public static native int setPath(String path);

    public static native int prepare(Object surface);

    public static native int onStart();

    public static native int onPause();

    public static native int onStop();

    public static native int main(int argc,Object argv);

}
