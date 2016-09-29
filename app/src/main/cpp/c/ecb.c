#include "../h/ecb.h"

unsigned char* KEY = "0123456789abcdef";//这里是密码长度16位

void ECB_Decrypt(ListP list) {
	int count = list->lenth / KEY_LENGTH;
	int index = 0;
	for (; index < count;index++){
		AES_Decrypt(list->p + index*KEY_LENGTH, KEY);
	}
	unsigned char * p = list->p + list->lenth;
	p  = '\0';
}

void ECB_Encrypt(ListP list){
	int count = list->lenth / KEY_LENGTH;
	int index = 0;
	for (; index < count; index++){
		AES_Encrypt(list->p + index*KEY_LENGTH, KEY);
	}
}