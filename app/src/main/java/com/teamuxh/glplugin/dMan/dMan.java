package com.teamuxh.glplugin.dMan;

import android.annotation.SuppressLint;
import android.app.Service;
import android.content.Context;
import android.content.Intent;
import android.graphics.Canvas;
import android.graphics.Point;
import android.os.IBinder;
import android.os.Process;
import android.os.SystemClock;
import android.view.Display;
import android.view.View;

import androidx.annotation.Nullable;

import com.teamuxh.glplugin.Fs;
import com.teamuxh.glplugin.mics.logger;


@SuppressWarnings("JavaJniMissingFunction")
public class dMan extends View implements Runnable {

    int sw = 0;
    int sh = 0;
    int mFPS = 0;
    long mFpS시각 = 0;
    int mFpS카운터 = 0;
    Point sS;
    float den = 0;
    Context ctx;
    Display dps;
    int FPS = 60;
    long 수면시간;
    Thread m실;
    private static native void onDC(Canvas canvas,int w,int h,float d);
    private static native void fps(CharSequence fps);

    public dMan(Context context) {
        super(context);
        sS = new Point();
        dps = Fs.emWM.getDefaultDisplay();
        dps.getRealSize(sS);
        den = getResources().getDisplayMetrics().density;
        sw = sS.x;
        sh = sS.y;
        ctx = context;
        m실 = new Thread();
        m실.start();
    }

    @SuppressLint("DrawAllocation")
    @Override
    protected void onDraw(Canvas canvas) {
        super.onDraw(canvas);

        dps.getRealSize(sS);
        den = getResources().getDisplayMetrics().density;
        sw = sS.x;
        sh = sS.y;
        onDC(canvas,sw,sh,den);
        gFPS();
        invalidate();
    }

    public void gFPS(){
        if (SystemClock.uptimeMillis() - mFpS시각 > 1000){
            mFpS시각 = SystemClock.uptimeMillis();
            mFPS = mFpS카운터;
            mFpS카운터 = 0;
        } else {
            mFpS카운터++;
        }
        CharSequence cFPS = "FPS " + mFPS;
        fps(cFPS);
    }
    @Override
    public void run() {
        android.os.Process.setThreadPriority(Process.THREAD_PRIORITY_BACKGROUND);
        while (m실.isAlive() && m실.isInterrupted()){
            try {
                long 시각 = System.currentTimeMillis();
                postInvalidate();
                long d시각 = System.currentTimeMillis() - 시각;
                Thread.sleep(Math.max(Math.min(0,수면시간-d시각),수면시간));
            } catch (Exception e){
                Thread.currentThread().interrupt();
                return;
            }
        }
    }
}
