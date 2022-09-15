#include "math/mymath.h"
#include "preprocess/preprocess.h"
#include "utils/myutils.h"

// H(8, sqrt), K(64, cbrt)값 구하기
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

void initialize(char *text)
{
	unsigned int *h = h_init();
	unsigned int *k = k_init();
	unsigned int *w = queuing(text);
}

#define EXTRACT_BINARY_UNITS(var) (var & 0x01 ? 0x01 : 0x00)
#define BINARY32PRINTF(var) for (size_t j = 0; j < 32; j++) printf("%d", EXTRACT_BINARY_UNITS(var >> (31 - j)))
#include <stdio.h>
int main()
{
	char*a = "hello world";

	unsigned int *h = h_init();
	unsigned int *k = k_init();
	unsigned int *w = queuing(a);

	printf("\n[H]");
	for (size_t i = 0; i < 8; i++)
	{
		if (i % 8 == 0)
			printf("\n");
		printf("%08x ", h[i]);
	}
	printf("\n[K]");
	for (size_t i = 0; i < 64; i++)
	{
		if (i % 8 == 0)
			printf("\n");
		printf("%08x ", k[i]);
	}
	printf("\n[W]");
	for (size_t i = 0; i < 64; i++)
	{
		if (!(i % 2))
			printf("\n");
		BINARY32PRINTF(w[i]);
		printf(" ");
	}
	return 0;
}
