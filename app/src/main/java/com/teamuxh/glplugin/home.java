package com.teamuxh.glplugin;

import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.graphics.Color;
import android.net.Uri;
import android.os.Bundle;
import android.os.Process;
import android.provider.Settings;
import android.view.View;
import android.widget.ImageView;
import android.widget.LinearLayout;
import android.widget.Toast;

import soup.neumorphism.NeumorphCardView;
import soup.neumorphism.NeumorphTextView;

public class home extends Activity {

    private NeumorphCardView start,stop;
    private Context 함유량;
    private NeumorphTextView txtCore;
    private int 내부_요청_코드_오버레이 = 7965;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(View.inflate(getApplicationContext(),R.layout.home,null));
        start = findViewById(R.id.start);
        stop = findViewById(R.id.stop);
        txtCore = findViewById(R.id.txtCore);

        함유량 = this;
        오버레이확인(내부_요청_코드_오버레이);

        start.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                start.setShapeType(2);
                stop.setShapeType(0);
                stop.setEnabled(true);
                start.setEnabled(false);
                txtCore.setText("코어 러닝");
                txtCore.setTextColor(Color.GREEN);
                startService(new Intent(home.this,Fs.class));
                Toast.makeText(home.this,"Started",Toast.LENGTH_LONG).show();
            }
        });
        stop.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                start.setShapeType(0);
                stop.setShapeType(2);
                stop.setEnabled(false);
                start.setEnabled(true);
                txtCore.setText("코어가 실행되지 않음");
                txtCore.setTextColor(Color.RED);
                stopService(new Intent(home.this,Fs.class));
                Toast.makeText(home.this,"Stopped",Toast.LENGTH_LONG).show();
            }
        });
    }
    private void 오버레이확인(int 요청_코드){
        if (!Settings.canDrawOverlays(함유량)){
            Intent intent = new Intent(Settings.ACTION_MANAGE_OVERLAY_PERMISSION, Uri.parse("package:" + getApplicationContext().getPackageName()));
            startActivityForResult(intent, 요청_코드);
            android.os.Process.killProcess(Process.myPid());
        }
    }
    static {
        System.loadLibrary("teamUxHGl");
    }
}
