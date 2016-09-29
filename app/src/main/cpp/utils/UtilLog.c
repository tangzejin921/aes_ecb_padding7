//
// Created by tangzejin on 2016/9/29.
//

#include "../h/utilLog.h"


void log_i(const char *s,const char *fmt,...){
    if(logOpen){
        __android_log_print(ANDROID_LOG_INFO,logTag,s,fmt);
    }
}
void log_e(const char *s,const char *fmt,...){
    if(logOpen){
        __android_log_print(ANDROID_LOG_ERROR,logTag,s,fmt);
    }
}
void printf(const char *s,const char *fmt,...){
    if(logOpen){
        __android_log_print(ANDROID_LOG_INFO,logTag,s,fmt);
    }
}