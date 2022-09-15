#include "mysha256.h"

//마무리 작업
char *finalize(char *text)
{
	unsigned int *comp = compression(text);
	unsigned int *h = h_init();
	static char final[64] = {
		0,
	};
	char *base = "0123456789abcdef";
	for (unsigned int i = 0; i < 8; i++)
		h[i] += comp[i];
	for (unsigned int i = 0; i < 64; i++)
		final[i] = base[h[i / 8] >> (28 - (i % 8) * 4) & 0x0f];
	return final;
}

#include <unistd.h>
//문자열 출력을 위한 main문
//출력을 위해 표준 입출력 라이브러리인 unistd.h 사용 불가피
int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		write(1, "input one argument please\n", 27);
		return 1;
	}
	write(1, finalize(argv[1]), 64);
	write(1, "\n", 1);
	return 0;
}
