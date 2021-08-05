//
// Created by hurri on 25-07-2021.
//

#ifndef GLPLUGIN_GRP_H
#define GLPLUGIN_GRP_H
#include <jni.h>
#include "struct.h"
#include "canvas.h"

class grp {
private:

public:
    JNIEnv *env;
    jobject grpB;
    jmethodID textStyle;
    jmethodID textSize;
    jmethodID textColor;
    jmethodID strokeWidth;
    jmethodID antiAlias;
    jobject sFill, sStroke, sSFnD;
    grp(JNIEnv *env){
        this->env = env;
        jclass mGrp = env->FindClass("android/graphics/Paint");
        jmethodID initialize = env->GetMethodID(mGrp,"<init>","()V");
        this->grpB = env->NewGlobalRef(env->NewObject(mGrp,initialize));
        textStyle = env->GetMethodID(mGrp,"setStyle", "(Landroid/graphics/Paint$Style;)V");
        textSize = env->GetMethodID(mGrp,"setTextSize", "(F)V");
        textColor = env->GetMethodID(mGrp,"setColor", "(I)V");
        strokeWidth = env->GetMethodID(mGrp,"setStrokeWidth", "(F)V");
        antiAlias = env->GetMethodID(mGrp,"setAntiAlias", "(Z)V");
        env->DeleteLocalRef(mGrp);
        jclass sStyle = env->FindClass("android/graphics/Paint$Style");
        jfieldID id = env->GetStaticFieldID(sStyle,"FILL", "Landroid/graphics/Paint$Style;");
        sFill = env->NewGlobalRef(env->GetStaticObjectField(sStyle, id));
        id = env->GetStaticFieldID(sStyle, "STROKE", "Landroid/graphics/Paint$Style;");
        sStroke = env->NewGlobalRef(env->GetStaticObjectField(sStyle, id));
        id = env->GetStaticFieldID(sStyle, "FILL_AND_STROKE", "Landroid/graphics/Paint$Style;");
        sSFnD = env->NewGlobalRef(env->GetStaticObjectField(sStyle, id));
        env->DeleteLocalRef(sStyle);

    }
    void setStyle(Style style);
    void setTextSize(float size);
    void setColor(int colour);
    void setStroke(float size = 1.0f);
    void setAntiAlias(bool hd);
};


#endif //GLPLUGIN_GRP_H
