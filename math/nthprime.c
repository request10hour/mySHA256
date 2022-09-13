#include "mymath.h"
// nth prime number n번째 소수찾기
double nthprime(unsigned int a)
{
	if (a == 1)
		return 2;
	unsigned int count = 2;
	double ret = 3;
	while (1)
	{
		if (count == a)
			return ret;
		ret++;
		for (unsigned int i = 2; i < my_sqrt(ret) + 1; i++)
		{
			if ((unsigned int)ret % i == 0)
				break;
			if (((unsigned int)(my_sqrt(ret) + 1) - 1) == i)
				count++;
		}
	}
}
