//
// Created by tangzejin on 2016/9/29.
//

#ifndef AES_ECB_PADDING7_UTILLOG_H
#define AES_ECB_PADDING7_UTILLOG_H
#include <android/log.h>
#include "config.h"

#ifdef __cplusplus
extern "C" {
#endif

//#define LOGI(FORMAT,...) __android_log_print(ANDROID_LOG_INFO,"jni_test",FORMAT,__VA_ARGS__)
//#define LOGE(FORMAT,...) __android_log_print(ANDROID_LOG_ERROR,"jni_test",FORMAT,__VA_ARGS__)

void log_i(const char *s,const char *fmt, ...);
void log_e(const char *s,const char *fmt, ...);
void printf(const char *s,const char *fmt, ...);

#ifdef __cplusplus
}
#endif

#endif //AES_ECB_PADDING7_UTILLOG_H
