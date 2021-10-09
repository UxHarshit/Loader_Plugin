//
// Created by UxHurricane on 25-07-2021.
//

#ifndef GLPLUGIN_CANVAS_H
#define GLPLUGIN_CANVAS_H
#include <jni.h>
#include "struct.h"
#include "grp.h"
#include "../mics/mSc.h"
class canvas
{
private:
    bool HD;
    int mWidth;
    int mHeight;
    int mDensity;
    jmethodID dtC,dCc,dCb;
    jobject mCanvas;
    class grp *mTextDraw;
    class grp *mCircle;
    class grp *mSolid;
public:
    canvas(JNIEnv *env,int width,int height,float density,bool hd);
    JNIEnv *env;
    void mHD(bool mhd);
    void refresh(jobject canvas);
    float SS(float size);
    int SS(int size);
    void drawText(const char *text, float X, float Y, float size = 10, int textColor = 0xFFFFFFFF, int outlineColor = 0x0);
    void drawText(const wchar_t *text, float X, float Y, float size = 10, int textColor = 0xFFFFFFFF, int outlineColor = 0x0);
    void drawCircle(float x,float y,float radius,float thickness,int color = 0xFFFFFFFF);
    void drawBox(float x,float y,float width,float height,int color = 0xFFFFFFFF);
    void drawBox(Vector2 vecX,float width,float height,int color = 0xFFFFFFFF);
};



#endif //GLPLUGIN_CANVAS_H
