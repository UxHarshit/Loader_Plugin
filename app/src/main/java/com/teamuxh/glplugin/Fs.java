package com.teamuxh.glplugin;

import android.annotation.SuppressLint;
import android.app.Service;
import android.content.Context;
import android.content.Intent;
import android.graphics.Color;
import android.graphics.PixelFormat;
import android.graphics.drawable.GradientDrawable;
import android.os.Build;
import android.os.IBinder;

import android.view.GestureDetector;
import android.view.Gravity;
import android.view.LayoutInflater;
import android.view.MotionEvent;
import android.view.View;
import android.view.ViewConfiguration;
import android.view.ViewGroup;
import android.view.WindowManager;
import android.widget.CheckBox;
import android.widget.ImageView;
import android.widget.LinearLayout;
import android.widget.ScrollView;
import android.widget.Switch;
import android.widget.Toast;

import androidx.annotation.Nullable;

import com.teamuxh.glplugin.dMan.dMan;
import com.teamuxh.glplugin.mics.logger;


import soup.neumorphism.NeumorphCardView;

@SuppressWarnings("JavaJniMissingFunction")
public class Fs extends Service {

    private View 플로트뷰;
    LinearLayout mLin,header;
    WindowManager.LayoutParams layoutType;
    WindowManager mWM;
    public static WindowManager emWM;
    NeumorphCardView esp,aimbot,items,cars,settings;
    ScrollView layEsp,layAimbot,layItems,layCars,laySettings;
    ImageView icLogo,hide;
    GestureDetector gestureDetector;
    CheckBox showFPS;

    private static native void hd();
    private static native void mSwitch(int 안건ID);
    @Nullable
    @Override
    public IBinder onBind(Intent intent) {
        return null;
    }

    @Override
    public void onCreate() {
        super.onCreate();
        logger.doLog = true;
        보기만들기();
        dC(this);
    }

    @SuppressLint("WrongConstant")
    private void dC(Context context){
        dMan ov;
        int tp;
        emWM = (WindowManager) context.getSystemService(Context.WINDOW_SERVICE);
        ov = new dMan(context);
        tp = gLT();
        WindowManager.LayoutParams lp = new WindowManager.LayoutParams(-1,-1,tp,56,-3);
        if (Build.VERSION.SDK_INT >= 28){
            lp.layoutInDisplayCutoutMode = 1;
        }
        lp.x = 0;
        lp.y = 0;
        lp.gravity = 51;
        emWM.addView(ov, lp);
    }
    @Override
    public void onDestroy() {
        super.onDestroy();
        mWM.removeView(플로트뷰);
    }

    private int gLT(){
        if(Build.VERSION.SDK_INT >=26){
            return 2038;
        }
        if (Build.VERSION.SDK_INT >= 24){
            return 2002;
        }
        if (Build.VERSION.SDK_INT >= 23){
            return 2005;
        }
        return 2003;
    }
    @SuppressLint({"InflateParams", "ClickableViewAccessibility", "RtlHardcoded"})
    private void 보기만들기(){

        플로트뷰 = LayoutInflater.from(getApplicationContext()).inflate(R.layout.fs,null);

        mLin = 플로트뷰.findViewById(R.id.main);
        icLogo = 플로트뷰.findViewById(R.id.iclogo);
        hide = 플로트뷰.findViewById(R.id.hide);
        header = 플로트뷰.findViewById(R.id.header);
        esp = 플로트뷰.findViewById(R.id.esp);
        aimbot = 플로트뷰.findViewById(R.id.aimbot);
        items = 플로트뷰.findViewById(R.id.items);
        cars = 플로트뷰.findViewById(R.id.cars);
        settings = 플로트뷰.findViewById(R.id.settings);
        layEsp = 플로트뷰.findViewById(R.id.layesp);
        layAimbot = 플로트뷰.findViewById(R.id.layaimbot);
        layItems = 플로트뷰.findViewById(R.id.layitems);
        layCars = 플로트뷰.findViewById(R.id.laycars);
        laySettings = 플로트뷰.findViewById(R.id.laysettings);
        showFPS = 플로트뷰.findViewById(R.id.showFPS);

        esp.setOnClickListener(cl());
        aimbot.setOnClickListener(cl());
        cars.setOnClickListener(cl());
        items.setOnClickListener(cl());
        settings.setOnClickListener(cl());

        showFPS.setOnClickListener(mcl());
        GradientDrawable gradientDrawable = new GradientDrawable();
        gradientDrawable.setCornerRadius(20);
        gradientDrawable.setColor(Color.parseColor("#E4EBF5"));
        mLin.setBackground(gradientDrawable);
        gestureDetector = new GestureDetector(this,new STC());

        icLogo.setOnTouchListener(tl());

        hide.setOnClickListener(cl());
        mWM = (WindowManager) getApplicationContext().getSystemService(Context.WINDOW_SERVICE);

        header.setOnTouchListener(tl());
        if (Build.VERSION.SDK_INT >= 26){
            layoutType = new WindowManager.LayoutParams(-2,-2,2038, WindowManager.LayoutParams.FLAG_NOT_FOCUSABLE ,PixelFormat.TRANSPARENT);
        } else {
            layoutType = new WindowManager.LayoutParams(-2,-2,2002, WindowManager.LayoutParams.FLAG_NOT_FOCUSABLE, -3);
        }
        layoutType.gravity = Gravity.TOP|Gravity.LEFT;
        layoutType.x = 0;
        layoutType.y = 100;
        layoutType.height = WindowManager.LayoutParams.WRAP_CONTENT;
        layoutType.width = WindowManager.LayoutParams.WRAP_CONTENT;

        mWM.addView(플로트뷰,layoutType);

    }
    private View.OnTouchListener tl(){
        return new View.OnTouchListener() {
            private int 머리글자X;
            private int 머리글자Y;
            private float 초기터치X;
            private float 초기터치Y;


            @Override
            public boolean onTouch(View v, MotionEvent event) {
                if (gestureDetector.onTouchEvent(event)){
                    if (v.getId() != R.id.iclogo){
                        플로트뷰.setVisibility(View.VISIBLE);
                    } else {
                        mLin.setVisibility(View.VISIBLE);
                        icLogo.setVisibility(View.GONE);
                    }
                    return true;
                } else {
                    switch (event.getAction()){
                        case MotionEvent.ACTION_DOWN:
                            머리글자X = layoutType.x;
                            머리글자Y = layoutType.y;
                            초기터치X = event.getRawX();
                            초기터치Y = event.getRawY();
                            return true;
                        case  MotionEvent.ACTION_MOVE:
                            layoutType.x = 머리글자X + (int) (event.getRawX()- 초기터치X);
                            layoutType.y = 머리글자Y + (int) (event.getRawY()- 초기터치Y);
                            mWM.updateViewLayout(플로트뷰,layoutType);
                            return true;
                    }
                    return false;
                }
            }
        };
    }
    public View.OnClickListener cl(){
        return new View.OnClickListener() {
            @SuppressLint("NonConstantResourceId")
            @Override
            public void onClick(View v) {
                switch (v.getId()){
                    case  R.id.esp:
                        esp.setShapeType(2);
                        aimbot.setShapeType(0);
                        items.setShapeType(0);
                        cars.setShapeType(0);
                        settings.setShapeType(0);
                        layEsp.setVisibility(View.VISIBLE);
                        layAimbot.setVisibility(View.GONE);
                        layItems.setVisibility(View.GONE);
                        layCars.setVisibility(View.GONE);
                        laySettings.setVisibility(View.GONE);
                    break;
                    case R.id.aimbot:
                        esp.setShapeType(0);
                        aimbot.setShapeType(2);
                        items.setShapeType(0);
                        cars.setShapeType(0);
                        settings.setShapeType(0);
                        layEsp.setVisibility(View.GONE);
                        layAimbot.setVisibility(View.VISIBLE);
                        layItems.setVisibility(View.GONE);
                        layCars.setVisibility(View.GONE);
                        laySettings.setVisibility(View.GONE);
                    break;
                    case R.id.items:
                        esp.setShapeType(0);
                        aimbot.setShapeType(0);
                        items.setShapeType(2);
                        cars.setShapeType(0);
                        settings.setShapeType(0);
                        layEsp.setVisibility(View.GONE);
                        layAimbot.setVisibility(View.GONE);
                        layItems.setVisibility(View.VISIBLE);
                        layCars.setVisibility(View.GONE);
                        laySettings.setVisibility(View.GONE);
                    break;
                    case R.id.cars:
                        esp.setShapeType(0);
                        aimbot.setShapeType(0);
                        items.setShapeType(0);
                        cars.setShapeType(2);
                        settings.setShapeType(0);
                        layEsp.setVisibility(View.GONE);
                        layAimbot.setVisibility(View.GONE);
                        layItems.setVisibility(View.GONE);
                        layCars.setVisibility(View.VISIBLE);
                        laySettings.setVisibility(View.GONE);
                    break;
                    case R.id.settings:
                        esp.setShapeType(0);
                        aimbot.setShapeType(0);
                        items.setShapeType(0);
                        cars.setShapeType(0);
                        settings.setShapeType(2);
                        layEsp.setVisibility(View.GONE);
                        layAimbot.setVisibility(View.GONE);
                        layItems.setVisibility(View.GONE);
                        layCars.setVisibility(View.GONE);
                        laySettings.setVisibility(View.VISIBLE);
                    break;
                    case R.id.hide:
                        mLin.setVisibility(View.GONE);
                        icLogo.setVisibility(View.VISIBLE);
                    break;
                    case R.id.iclogo:
                        mLin.setVisibility(View.VISIBLE);
                        icLogo.setVisibility(View.GONE);
                        Toast.makeText(Fs.this,"Clicked",Toast.LENGTH_LONG).show();
                    break;
                }
            }
        };
    };

    public View.OnClickListener mcl(){
        return new View.OnClickListener(){
            @SuppressLint("NonConstantResourceId")
            @Override
            public void onClick(View v) {
                switch (v.getId()){
                    case R.id.showFPS:
                        if (showFPS.isChecked()) {
                            logger.LogD("Show FPS 활성화");
                            mSwitch(60);
                        } else {
                            mSwitch(60);
                            logger.LogD("Show FPS 장애가있는");
                        }
                        break;
                }
            }
        };
    }

    class STC extends GestureDetector.SimpleOnGestureListener{
        @Override
        public boolean onSingleTapUp(MotionEvent e) {
            return true;
        }
    }
}
