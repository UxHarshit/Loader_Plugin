//
// Created by hurri on 25-07-2021.
//

#include "grp.h"
#include <wchar.h>
#include "canvas.h"
#include "rect.h"
jstring wcstojstr2(JNIEnv *env, const wchar_t *input) {
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

void grp::setTextSize(float size) {
    env->CallVoidMethod(this->grpB, this->textSize,size);
}
void grp::setStyle(Style style) {
    if (style == Style::FILL)
        env->CallVoidMethod(this->grpB, this->textStyle,this->sFill);
    if (style == Style::STROKE)
        env->CallVoidMethod(this->grpB,this->textStyle, this->sStroke);
    if (style == Style::FILL_AND_STROKE)
        env->CallVoidMethod(this->grpB, this->textStyle, this->sSFnD);
}
void grp::setStroke(float size) {
    env->CallVoidMethod(this->grpB, this->strokeWidth,size);
}
void grp::setColor(int colour) {
    env->CallVoidMethod(this->grpB, this->textColor,colour);
}
void grp::setAntiAlias(bool hd) {
    env->CallVoidMethod(this->grpB, this->antiAlias,hd);
}
