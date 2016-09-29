#include <jni.h>
#include <string>
#include "h/pkcs7padding.h"
#include "h/ecb.h"
#include "h/b64.h"
#include "h/aes.h"

extern "C"
JNIEXPORT jbyteArray JNICALL
Java_com_jkwy_libs_aes_UtilAes_b64Encode(JNIEnv *env, jclass type, jbyteArray bs) {
    jsize size = env->GetArrayLength(bs);
    jbyte *bsp = env->GetByteArrayElements(bs, NULL);

    List list = {size, (unsigned char *) bsp};
    ListP lp = &list;
    b64_encode(lp);
    env->ReleaseByteArrayElements(bs, bsp, 0);

    jbyteArray array = env->NewByteArray(lp->lenth);
    env->SetByteArrayRegion(array,0,lp->lenth,(const jbyte*)lp->p);
    free(lp->p);
    return array;
}

extern "C"
JNIEXPORT jbyteArray JNICALL
Java_com_jkwy_libs_aes_UtilAes_b64Decode(JNIEnv *env, jclass type, jbyteArray bs) {
    jsize size = env->GetArrayLength(bs);
    jbyte *bsp = env->GetByteArrayElements(bs, NULL);

    List list = {size, (unsigned char *) bsp};
    ListP lp = &list;
    b64_decode(lp);

    jbyteArray array = env->NewByteArray(lp->lenth);
    env->SetByteArrayRegion(array,0,lp->lenth,(const jbyte*)lp->p);
    env->ReleaseByteArrayElements(bs, bsp, 0);
    return array;
}

extern "C"
JNIEXPORT jstring JNICALL
Java_com_jkwy_libs_aes_UtilAes_encode(JNIEnv *env, jclass type, jstring jstr) {
    const char *str = env->GetStringUTFChars(jstr, 0);

    List list = {strlen(str), (unsigned char *) str};
    ListP lp = &list;
    env->ReleaseStringUTFChars(jstr, PKCS7Padding(lp));
    ECB_Encrypt(lp);
    free(b64_encode(lp));
    jstring ret = env->NewStringUTF((const char *) lp->p);
    free(lp->p);
    return ret;
}

extern "C"
JNIEXPORT jbyteArray JNICALL
Java_com_jkwy_libs_aes_UtilAes_decode(JNIEnv *env, jclass type, jstring jstr) {

    const char *str = env->GetStringUTFChars(jstr, 0);

    List list = {strlen(str), (unsigned char *) str};
    ListP lp = &list;

    b64_decode(lp);
    ECB_Decrypt(lp);
    PKCS7UnPadding(lp);

    jbyteArray array = env->NewByteArray(lp->lenth);
    env->SetByteArrayRegion(array, 0, lp->lenth, (const jbyte*)lp->p);

    env->ReleaseStringUTFChars(jstr, str);
    return array;
    //这里转成string时数据不对会报错
//    jstring ret = env->NewStringUTF((const char *) lp->p);
//    jthrowable throwable = env->ExceptionOccurred();
//    if (throwable!= NULL){
//        env->ExceptionClear();
//        jclass newThrow = env->FindClass("java/lang/IllegalArgumentException");
//        if (newThrow!=NULL){
//            env->ThrowNew(newThrow,"无法解析的内容");
//        }
//    }
//
//    return ret;
}