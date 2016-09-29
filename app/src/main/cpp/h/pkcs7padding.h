#ifndef __PKCS7PADDING_H__
#define __PKCS7PADDING_H__
#include "aes.h"
#ifdef __cplusplus
extern "C" {
#endif
char* PKCS7Padding(ListP listp);
void PKCS7UnPadding(ListP listp);
#ifdef __cplusplus
}
#endif
#endif // !__PKCS7PADDING_H__