
//
// aes.h
// API for simple AES 128-bit.
//来自 https://github.com/noahp/aes_c
#ifndef __AES_H_
#define __AES_H_

typedef struct {
	int lenth;
	unsigned char* p;
} List, * ListP;

#ifdef __cplusplus
extern "C" {
#endif

// Encrypt in-place. Data and key should be 16 bytes.
void AES_Encrypt(unsigned char *data, unsigned char *key);
void AES_Decrypt(unsigned char *data, unsigned char *key);

#ifdef __cplusplus
}
#endif

#endif // !__AES_H_