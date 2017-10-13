package com.robin.starplayer.debug;

import android.util.Log;

/**
 * Created by robin on 2017/9/15.
 */

public class LogUtils {
    private static final String TAG = "StarPlayer";

    private static boolean DEBUG = true;

    public static void e(String tag,String msg){
        if(DEBUG){
            Log.e(tag,msg);
        }
    }

    public static void e(String msg){
        if(DEBUG){
            Log.e(TAG,msg);
        }
    }
}
