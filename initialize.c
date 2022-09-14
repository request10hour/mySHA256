#include "math/mymath.h"
#include "preprocess/preprocess.h"
#include "utils/myutils.h"
#define HCOUNT 8
#define KCOUNT 32
#include <stdio.h>

// H(8, sqrt), K(64, cbrt)값 구하기
unsigned int *h_k_init(/*int count, double (*f)*/)
{
	double sqr;
	unsigned long long a;
	for (unsigned int i = 0; i < 8; i++)
	{
		sqr = my_sqrt(nthprime(i + 1));
		while (sqr >= 2)
			sqr--;
		my_memmove(&a, &sqr, sizeof(unsigned long long));
		printf("%.20f\n", sqr);
		unsigned int b = 0xffffffff & (a >> 20);
		printf("%08x\n", b);
	}
}

// void initialize(char *text)
// {
// 	unsigned int *h;
// 	unsigned int *k;
// 	unsigned int *w = queuing(text);
// }

int main()
{
	h_k_init();
	return 0;
}
