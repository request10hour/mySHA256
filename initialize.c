#include "math/mymath.h"
#include "preprocess/preprocess.h"
#include "utils/myutils.h"
#include "mysha256.h"

// H값 구하기
unsigned int *h_init()
{
	static unsigned int h[8];
	double sqr;
	unsigned long long a;
	for (unsigned int i = 0; i < 8; i++)
	{
		sqr = my_sqrt(nthprime(i + 1));
		while (sqr >= 2)
			sqr--;
		my_memmove(&a, &sqr, sizeof(unsigned long long));
		h[i] = 0xffffffff & (a >> 20);
	}
	return h;
}

// K값 구하기
unsigned int *k_init()
{
	static unsigned int k[64];
	double cbr;
	unsigned long long a;
	for (unsigned int i = 0; i < 64; i++)
	{
		cbr = my_cbrt(nthprime(i + 1));
		while (cbr >= 2)
			cbr--;
		my_memmove(&a, &cbr, sizeof(unsigned long long));
		k[i] = 0xffffffff & (a >> 20);
	}
	return k;
}

// W값 구하기
unsigned int *w_init(char *text)
{
	static unsigned int w[64] = {
		0,
	};
	unsigned char *pp = preprocess(text);
	for (unsigned int i = 0; i < 16; i++)
	{
		for (unsigned int j = 0; j < 4; j++)
		{
			w[i] = w[i] << 8;
			w[i] |= pp[i * 4 + j];
		}
	}
	unsigned int s0, s1;
	for (unsigned int i = 16; i < 64; i++)
	{
		s0 = RIGHTROTATE(w[i - 15], 7) ^ RIGHTROTATE(w[i - 15], 18) ^ RIGHTSHIFT(w[i - 15], 3);
		s1 = RIGHTROTATE(w[i - 2], 17) ^ RIGHTROTATE(w[i - 2], 19) ^ RIGHTSHIFT(w[i - 2], 10);
		w[i] = w[i - 16] + s0 + w[i - 7] + s1;
	}

	return w;
}

// //아래는 INITIALIZE test를 위한 main문
// #include <stdio.h>
// #define EXTRACT_BINARY_UNITS(var) (var & 0x01 ? 0x01 : 0x00)
// #define BINARY32PRINTF(var)         \
// 	for (size_t j = 0; j < 32; j++) \
// 	printf("%d", EXTRACT_BINARY_UNITS(var >> (31 - j)))

// int main()
// {
// 	char *a = "hello world";

// 	unsigned int *h = h_init();
// 	unsigned int *k = k_init();
// 	unsigned int *w = w_init(a);

// 	printf("\n[H]");
// 	for (size_t i = 0; i < 8; i++)
// 	{
// 		if (i % 8 == 0)
// 			printf("\n");
// 		printf("%08x ", h[i]);
// 	}
// 	printf("\n[K]");
// 	for (size_t i = 0; i < 64; i++)
// 	{
// 		if (i % 8 == 0)
// 			printf("\n");
// 		printf("%08x ", k[i]);
// 	}
// 	printf("\n[W]");
// 	for (size_t i = 0; i < 64; i++)
// 	{
// 		if (!(i % 2))
// 			printf("\n");
// 		BINARY32PRINTF(w[i]);
// 		printf(" ");
// 	}
// 	return 0;
// }
