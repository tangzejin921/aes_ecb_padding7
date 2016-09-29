//#define _CRT_SECURE_NO_WARNINGS

#include <string.h>
#include "../h/pkcs7padding.h"


/*
产生了新的内存返回原来内存的指针
这里注意是否要在外部释放内存ss
*/
char* PKCS7Padding(ListP list){
	int padding = KEY_LENGTH - list->lenth % KEY_LENGTH;
	unsigned char* nb = (unsigned char*)malloc((list->lenth + padding + 1)*sizeof(unsigned char));
	int size = list->lenth + padding;
	nb[size] = '\0';
	int i = 0;
	for (; i < size; i++){
		if (i<list->lenth){
			nb[i] = *(list->p + i);
		}
		else{
			nb[i] = padding;
		}
	}
	list->lenth = size;
	char * ret = (char *)list->p;
	list->p = nb;
	return ret;
}

void PKCS7UnPadding(ListP list){
	int unpadding = *(list->p + (list->lenth - 1));
	list->p[list->lenth - unpadding] = '\0';
	list->lenth = list->lenth - unpadding;
}