//
// Created by UxHurricane on 25-07-2021.
//
#include <jni.h>
#include <string.h>
#include <stdio.h>
#include <string>
#include <sstream>
#include <iostream>
#include "graphics/canvas.h"
#include "mics/init.h"
#include <fstream>
#include <sys/time.h>
#include "mics/logs.h"
#include <ctime>

static canvas *lCanvas = 0;
long fTick = 0;
long eTick = 0;
long gTime = 0;
static std::string j2h(JNIEnv *env,jclass thiz,const jstring text)
{
    const jclass stringClass = env->GetObjectClass(text);
    const jmethodID getBytes = env->GetMethodID(stringClass, "getBytes", "(Ljava/lang/String;)[B");
    const jbyteArray stringJbytes = (jbyteArray) env->CallObjectMethod(text, getBytes, env->NewStringUTF("UTF-8"));
    size_t length = (size_t) env->GetArrayLength(stringJbytes);
    jbyte* pBytes = env->GetByteArrayElements(stringJbytes, NULL);
    return std::string((char *)pBytes, length);
}

const char *cFPS = "           Team UxH";

void nFps(JNIEnv * env , jclass clazz ,jstring fps){
    mFps = j2h(env,clazz,fps);
}


void nHD(JNIEnv * env , jclass clazz ){

}

void mFunction(JNIEnv *env,jclass clazz,jint i){
    LOGD("%d",i);
    switch (i) {
        case 60:
            if (bFPS){
                bFPS = false;
            } else
                bFPS = true;
            break;
        case 1080:
            if (sHD){
                sHD = false;
                lCanvas->mHD(false);
            } else {
                sHD = true;
                lCanvas->mHD(true);
            }
            break;
    }
}

void nDraw(JNIEnv *env,jclass clazz, jobject canvas,jint w, jint h,jfloat d){
    bool hs = false;
    gSW = w;
    gSH = h;
    LOGD("%d",gSW);
    LOGD("%d",gSH);
    fpsW = gSW/25;
    fpsH = gSH/25;
    if(!lCanvas){
        lCanvas = new class canvas(env,w,h,d,hs);
    }
    lCanvas->refresh(canvas);
    lCanvas->drawText(cFPS,gSW/10,gSH-200,20,0xFFFFFFFF,0x0);
    if (bFPS){
        lCanvas->drawText(mFps.c_str(),300,fpsH ,20,0xFFFFFFFF,0x0);
    }

}

int Reg1(JNIEnv * env){
    JNINativeMethod method[] = {
            {"hd","()V",(void *) nHD},
            {"mSwitch","(I)V",(void *) mFunction}
    };
    jclass clazz = env->FindClass("com/teamuxh/glplugin/Fs");
    if (!clazz)
        return -1;
    if (env->RegisterNatives(clazz,method,sizeof(method)/sizeof(method[0])) != 0)
        return -1;
    return 0;
}

int Reg2(JNIEnv * env){
    JNINativeMethod method[] = {
            {"onDC","(Landroid/graphics/Canvas;IIF)V",(void *) nDraw},
            {"fps","(Ljava/lang/CharSequence;)V",(void *) nFps}
    };
    jclass clazz = env->FindClass("com/teamuxh/glplugin/dMan/dMan");
    if (!clazz)
        return -1;
    if (env->RegisterNatives(clazz,method,sizeof(method)/sizeof(method[0])) != 0)
        return -1;
    return 0;
}


JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *vm, void *unused){
    JNIEnv *env;
    vm->GetEnv((void **) &env,JNI_VERSION_1_6);
    if (Reg1(env) != 0)
        return -1;
    if (Reg2(env) != 0)
        return -1;
    return JNI_VERSION_1_6;
}