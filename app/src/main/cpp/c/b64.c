
/**
* `encode.c' - b64
*
* copyright (c) 2014 joseph werle
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "../h/b64.h"

/**
 * 计算这个char 在b64_table中的下标
 */
int getIndex(unsigned char* cp){
	char c = *cp;
	if ('A'<=c && c<='Z'){
		*cp=c - 'A';
		return *cp;
	}else if ('a' <= c&&c <= 'z'){
		*cp = c - 'a' + 26;
		return *cp;
	}else if ('0' <= c&&c <= '9'){
		*cp = c - '0' + 52;
		return *cp;
	} else if(c=='+'){
		*cp = 62;
		return *cp;
	} else if (c == '/'){
		*cp = 63;
		return *cp;
	}
	return -1;
}

/*
产生了新的内存返回原来内存的指针
这里注意是否要在外部释放内存
*/
unsigned char * b64_encode(ListP lp) {
	int len = lp->lenth;
	const unsigned char *src = lp->p;
	unsigned char *ret = lp->p;

	int i = 0;
	int j = 0;
	unsigned char *enc = NULL;
	int size = 0;
	unsigned char buf[4];
	unsigned char tmp[3];

	// alloc
	int newLen = (len / 3) * 4 + (len % 3 > 0 ? 4 : 0);
	newLen += newLen/76;
	enc = (char *)malloc(newLen+1);
	if (NULL == enc) { return NULL; }

	// parse until end of source
	while (len--) {
		// read up to 3 bytes at a time into `tmp'
		tmp[i++] = *(src++);

		// if 3 bytes read then encode into `buf'
		if (3 == i) {
			buf[0] = (tmp[0] & 0xfc) >> 2;
			buf[1] = ((tmp[0] & 0x03) << 4) + ((tmp[1] & 0xf0) >> 4);
			buf[2] = ((tmp[1] & 0x0f) << 2) + ((tmp[2] & 0xc0) >> 6);
			buf[3] = tmp[2] & 0x3f;

			// allocate 4 new byts for `enc` and
			// then translate each encoded buffer
			// part by index from the base 64 index table
			// into `enc' unsigned char array
			for (i = 0; i < 4; ++i) {
				enc[size++] = b64_table[buf[i]];
			}
			if (size%77==76){//这里加'\n'
				enc[size++] = '\n';
			}
			// reset index
			i = 0;
		}
	}

	// remainder
	if (i > 0) {
		// fill `tmp' with `\0' at most 3 times
		for (j = i; j < 3; ++j) {
			tmp[j] = '\0';
		}

		// perform same codec as above
		buf[0] = (tmp[0] & 0xfc) >> 2;
		buf[1] = ((tmp[0] & 0x03) << 4) + ((tmp[1] & 0xf0) >> 4);
		buf[2] = ((tmp[1] & 0x0f) << 2) + ((tmp[2] & 0xc0) >> 6);
		buf[3] = tmp[2] & 0x3f;

		// perform same write to `enc` with new allocation
		for (j = 0; (j < i + 1); ++j) {
			enc[size++] = b64_table[buf[j]];
		}

		// while there is still a remainder
		// append `=' to `enc'
		while (i++ < 3) {
			enc[size++] = '=';
		}
	}

	// Make sure we have enough space to add '\0' character at end.
	enc[size] = '\0';

	lp->p = enc;
	lp->lenth = size;

	return ret;
}


void b64_decode(ListP lp) {
	char * src = lp->p;
	int len = lp->lenth;

	int i = 0;
	int j = 0;
	int l = 0;
	int size = 0;
	unsigned char buf[3];
	unsigned char tmp[4];


	// parse until end of source
	while (len--) {
		// break if char is `=' or not base64 char
		if ('=' == src[j]) {
			j++;
			continue;
		}
		if (!(isalnum(src[j]) || '+' == src[j] || '/' == src[j])) {
			j++;
			continue;
		}

		// read up to 4 bytes at a time into `tmp'
		tmp[i++] = src[j++];

		// if 4 bytes read then decode into `buf'
		if (4 == i) {
			// translate values in `tmp' from table
			for (i = 0; i < 4; ++i) {
				getIndex(&tmp[i]);
			}
			// decode
			buf[0] = (tmp[0] << 2) + ((tmp[1] & 0x30) >> 4);
			buf[1] = ((tmp[1] & 0xf) << 4) + ((tmp[2] & 0x3c) >> 2);
			buf[2] = ((tmp[2] & 0x3) << 6) + tmp[3];

			for (i = 0; i < 3; ++i) {
				src[size++] = buf[i];
			}

			// reset
			i = 0;
		}
	}

	// remainder
	if (i > 0) {
		// fill `tmp' with `\0' at most 4 times
		for (j = i; j < 4; ++j) {
			tmp[j] = '\0';
		}

		// translate remainder
		for (j = 0; j < 4; ++j) {
			// find translation char in `b64_table'
			getIndex(&tmp[j]);
		}

		// decode remainder
		buf[0] = (tmp[0] << 2) + ((tmp[1] & 0x30) >> 4);
		buf[1] = ((tmp[1] & 0xf) << 4) + ((tmp[2] & 0x3c) >> 2);
		buf[2] = ((tmp[2] & 0x3) << 6) + tmp[3];

		for (j = 0; (j < i - 1); ++j) {
			src[size++] = buf[j];
		}
	}

	src[size] = '\0';

	lp->p = src;
	lp->lenth = size;
}
