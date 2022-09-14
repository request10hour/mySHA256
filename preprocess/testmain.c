#include <stdio.h>
#define EXTRACT_BINARY_UNITS(var) (var & 0x01 ? 0x01 : 0x00)
#include "preprocess.h"

int main(int argc, char **argv)
{
	printf("origin text : %s\n\n", argv[1]);

	// preprocess test
	printf("preprocessed\n");
	char *chunk = preprocess(argv[1]);
	for (size_t j = 0; j < 64; j++)
	{
		if (!(j % 8))
			printf("\n");
		for (size_t i = 0; i < 8; i++)
		{
			printf("%d", EXTRACT_BINARY_UNITS(chunk[j] >> (7 - i)));
		}
		printf(" ");
	}
	printf("\n");

	// queuing test
	printf("\n");
	printf("this is W\n");
	unsigned int *w = queuing(argv[1]);
	for (size_t j = 0; j < 64; j++)
	{
		if (!(j % 2))
			printf("\n");
		for (size_t i = 0; i < 32; i++)
		{
			printf("%d", EXTRACT_BINARY_UNITS(w[j] >> (31 - i)));
		}
		printf(" ");
	}
	printf("\n");

	return 0;
}
