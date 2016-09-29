#ifndef __ECB_H__
#define __ECB_H__
#include "aes.h"
#ifdef __cplusplus
extern "C" {
#endif
void ECB_Encrypt(ListP listp);
void ECB_Decrypt(ListP listp);
#ifdef __cplusplus
}
#endif
#endif // !__ECB_H__



