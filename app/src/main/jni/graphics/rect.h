//
// Created by hurri on 22-09-2021.
//

#ifndef GLPLUGIN_RECT_H
#define GLPLUGIN_RECT_H

#include <jni.h>


class rect {
public:
    JNIEnv *env;
    jobject rectObj;

    jfieldID leftId, topId, rightId, bottomId;
    rect(JNIEnv *env){
        this->env = env;

        jclass rectClass = env->FindClass("android/graphics/Rect");
        jmethodID init = env->GetMethodID(rectClass, "<init>", "()V");
        this->rectObj = env->NewGlobalRef(env->NewObject(rectClass, init));
        leftId = env->GetFieldID(rectClass, "left", "I");
        topId = env->GetFieldID(rectClass, "top", "I");
        rightId = env->GetFieldID(rectClass, "right", "I");
        bottomId = env->GetFieldID(rectClass, "bottom", "I");
        env->DeleteLocalRef(rectClass);
    }
    int getLeft();
    int getRight();
    int getTop();
    int getBottom();
    int getWidth();
    int getHeight();
};


#endif //GLPLUGIN_RECT_H
