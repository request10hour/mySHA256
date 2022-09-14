#include "preprocess.h"

unsigned char *preprocess(char *text)
{
	static unsigned char chunk[64] = {
		0,
	};
	unsigned int i = 0;
	while (text[i])
	{
		chunk[i] = text[i];
		i++;
	}
	chunk[i] = 0x80;
	chunk[63] = i * 8;
	return chunk;
}

unsigned int *queuing(char *text)
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
	return w;
}
