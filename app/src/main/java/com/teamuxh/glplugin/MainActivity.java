package com.teamuxh.glplugin;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;

import androidx.appcompat.app.AppCompatActivity;

import soup.neumorphism.NeumorphButton;

public class MainActivity extends Activity {

    NeumorphButton login;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(View.inflate(getApplicationContext(),R.layout.activity_main,null));
        login = findViewById(R.id.neumorphButton2);

        login.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent log = new Intent();
                log.setClass(MainActivity.this,home.class);
                startActivity(log);
                finish();
            }
        });


    }
}