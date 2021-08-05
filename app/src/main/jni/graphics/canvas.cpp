//
// Created by UxHurricane on 25-07-2021.
//

#include "canvas.h"


jstring wcstojstr(JNIEnv *env, const wchar_t *input) {
    jobject bb = env->NewDirectByteBuffer((void *) input, wcslen(input) * sizeof(wchar_t));
    static jstring UTF32LE = 0;
    if (!UTF32LE)
        UTF32LE = (jstring) env->NewGlobalRef(env->NewStringUTF("UTF-32LE"));

    static jclass charsetClass = 0;
    if (!charsetClass)
        charsetClass = env->FindClass("java/nio/charset/Charset");

    static jmethodID forNameMethod = 0;
    if (!forNameMethod)
        forNameMethod = env->GetStaticMethodID(charsetClass, "forName", "(Ljava/lang/String;)Ljava/nio/charset/Charset;");

    static jobject charset = 0;
    if (!charset)
        charset = env->NewGlobalRef(env->CallStaticObjectMethod(charsetClass, forNameMethod, UTF32LE));

    static jmethodID decodeMethod = 0;
    if (!decodeMethod)
        decodeMethod = env->GetMethodID(charsetClass, "decode", "(Ljava/nio/ByteBuffer;)Ljava/nio/CharBuffer;");

    jobject cb = env->CallObjectMethod(charset, decodeMethod, bb);

    static jclass charBufferClass = 0;
    if (!charBufferClass)
        charBufferClass = env->FindClass("java/nio/CharBuffer");

    static jmethodID toStringMethod = 0;
    if (!toStringMethod)
        toStringMethod = env->GetMethodID(charBufferClass, "toString", "()Ljava/lang/String;");

    auto ret = (jstring) env->CallObjectMethod(cb, toStringMethod);

    env->DeleteLocalRef(bb);
    env->DeleteLocalRef(cb);

    return ret;
}

canvas::canvas(JNIEnv *env, int width, int height, float density, bool hd) {
    this->env = env;
    this->mWidth = width;
    this->mHeight = height;
    this->mDensity = density;
    this->HD = hd;

    jclass mCanvas = env->FindClass("android/graphics/Canvas");
    this->dtC = env->GetMethodID(mCanvas,"drawText","(Ljava/lang/String;FFLandroid/graphics/Paint;)V");
    env->DeleteLocalRef(mCanvas);

    this->mTextDraw = new grp(this->env);
    mTextDraw->setStyle(Style::FILL);
    mTextDraw->setAntiAlias(true);



}
void canvas::mHD(bool mhd) {
    this->HD = mhd;
    mTextDraw->setAntiAlias(mhd);
}

void canvas::drawText(const char *text, float X, float Y, float size, int textColor, int outlineColor) {
    grp *mGrp = this->mTextDraw;
    mGrp->setTextSize(this->SS(size));
    jstring txt = env->NewStringUTF(text);
    if (!HD){
        mGrp->setColor(outlineColor);
        env->CallVoidMethod(this->mCanvas, this->dtC, txt, X - 1,Y - 1,mGrp->grpB );
        env->CallVoidMethod(this->mCanvas, this->dtC, txt, X + 1,Y + 1,mGrp->grpB );
        env->CallVoidMethod(this->mCanvas, this->dtC, txt, X - 1,Y + 1,mGrp->grpB );
        env->CallVoidMethod(this->mCanvas, this->dtC, txt, X + 1,Y - 1,mGrp->grpB );
    }
    mGrp->setColor(textColor);
    env->CallVoidMethod(this->mCanvas, this->dtC,txt,X,Y,mGrp->grpB);
    env->DeleteLocalRef(txt);
}

void canvas::drawText(const wchar_t *text, float X, float Y, float size, int textColor,
                      int outlineColor) {
    grp *mGrp = this->mTextDraw;
    mGrp->setTextSize(this->SS(size));
    jstring cTxt = wcstojstr(env, text);
    if (!HD){
        mGrp->setColor(outlineColor);
        env->CallVoidMethod(this->mCanvas, this->dtC, cTxt, X - 1,Y - 1,mGrp->grpB );
        env->CallVoidMethod(this->mCanvas, this->dtC, cTxt, X + 1,Y + 1,mGrp->grpB );
        env->CallVoidMethod(this->mCanvas, this->dtC, cTxt, X - 1,Y + 1,mGrp->grpB );
        env->CallVoidMethod(this->mCanvas, this->dtC, cTxt, X + 1,Y - 1,mGrp->grpB );
    }
    mGrp->setColor(textColor);
    env->CallVoidMethod(this->mCanvas, this->dtC,cTxt,X,Y,mGrp->grpB);
    env->DeleteLocalRef(cTxt);
}

float canvas::SS(float size) {
    return size * mDensity;
}

int canvas::SS(int size) {
    return (int )((float) size * mDensity );
}

void canvas::refresh(jobject canvas) {
    this->mCanvas = canvas;
}
