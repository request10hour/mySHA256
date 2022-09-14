//테스트 main
#include <stdio.h>
#include <math.h>
#include "mymath.h"
int main()
{
	// //원본 sqrt와 비교
	// for (unsigned int i = 0; i < 100; i++)
	// {
	// 	printf("[%d]\norig : %.51f\nmine : %.51f\n", i, sqrt(i), my_sqrt(i));
	// }
	// // cbrt
	// for (unsigned int i = 0; i < 100; i++)
	// {
	// 	printf("[%d]\ncbrt : %.51f\n", i, my_cbrt(i));
	// }
	// H값 구하기
	double sqr;
	int a;
	printf("[H value] : \n");
	for (unsigned int i = 0; i < 8; i++)
	{
		sqr = my_sqrt(nthprime(i + 1));
		// printf("[%f - %d = %f]", sqr, (int)sqr, sqr - (int)sqr);
		// printf("[%f]", (sqr - (int)sqr) * 0x100000000);
		a = (unsigned)((sqr - (int)sqr) * 0x100000000);
		// printf("%u, %x\n", a, a);
		printf("%08x\n", a);
	}
	// K값 구하기
	printf("\n[K value] : \n");
	for (unsigned int i = 0; i < 64; i++)
	{
		sqr = my_cbrt(nthprime(i + 1));
		// printf("[%f - %d = %f]", sqr, (int)sqr, sqr - (int)sqr);
		// printf("[%f]", (sqr - (int)sqr) * 0x100000000);
		a = (unsigned)((sqr - (int)sqr) * 0x100000000);
		// printf("%u, %x\n", a, a);
		printf("%08x\n", a);
	}
	// //prime
	// for (unsigned int i = 1; i <= 100; i++)
	// {
	// 	printf("%dth prime : %f\n", i, nthprime(i));
	// }
	return 0;
}
