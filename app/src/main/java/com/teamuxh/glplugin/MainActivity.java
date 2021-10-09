package com.teamuxh.glplugin;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;

import androidx.appcompat.app.AppCompatActivity;

import java.io.DataOutputStream;
import java.io.IOException;

import soup.neumorphism.NeumorphButton;

public class MainActivity extends Activity {

    NeumorphButton login;
    Process process;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(View.inflate(getApplicationContext(),R.layout.activity_main,null));
        login = findViewById(R.id.neumorphButton2);

        login.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                //shell("su -c ./data/tmp/gcore");
                Intent log = new Intent();
                log.setClass(MainActivity.this,home.class);
                startActivity(log);
                finish();
            }
        });


    }

    public void shell(String str){
        DataOutputStream dataOutputStream = null;
        try {
            process = Runtime.getRuntime().exec(str);
        } catch (IOException e) {
            e.printStackTrace();
            process = null;
        }
        if (process != null) {
            dataOutputStream = new DataOutputStream(process.getOutputStream());
        }
        try {
            dataOutputStream.flush();
        } catch (IOException e2) {
            e2.printStackTrace();
        }
        try {
            process.waitFor();
        } catch (InterruptedException e3) {
            e3.printStackTrace();
        }
    }
}