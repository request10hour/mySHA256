#include "mymath.h"
// newton-raphson method 사용

// square root 제곱근
double my_sqrt(double n)
{
	if (!n)
		return 0;
	double x, xtmp;
	unsigned int maxtry = 0;
	x = n;
	// uintmax근처에서 22를 최대연산횟수로봄(실행결과추론)
	while (maxtry < 23)
	{
		maxtry++;
		xtmp = (x + n / x) / 2;
		if (x == xtmp)
			break;
		else
			x = xtmp;
	}
	return x;
}
// cube root 세제곱근
double my_cbrt(double n)
{
	if (!n)
		return 0;
	double x, xtmp;
	unsigned int maxtry = 0;
	x = n;
	// uintmax근처에서 43를 최대연산횟수로봄(실행결과추론)
	while (maxtry < 44)
	{
		maxtry++;
		xtmp = (2 * x + n / (x * x)) / 3;
		if (x == xtmp)
			break;
		else
			x = xtmp;
	}
	return x;
}
