package com.teamuxh.glplugin.mics;

import android.util.Log;

public class logger {
    public static boolean doLog = false;
    private static final String Head = "TeamUxH";
    public static void LogE(String msg){
        if (doLog) {Log.e(Head,msg);}
    }
    public static void LogD(String msg){
        if (doLog) {Log.d(Head,msg);}
    }
}
