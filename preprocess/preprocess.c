#define EXTRACT_BINARY_UNITS(var) (var & 0x01 ? 0x01 : 0x00)
#define BINARY32PRINTF(var)         \
	for (size_t j = 0; j < 32; j++) \
	printf("%d", EXTRACT_BINARY_UNITS(var >> (31 - j)))
#include <stdio.h>

// text를 chunk로 바꾸기 (1byte 64block)
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
#define RIGHTROTATE(uint, num) ((uint >> num) | (uint << 32 - num))
#define RIGHTSHIFT(uint, num) (uint >> num)
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
	unsigned int s0, s1;
	for (unsigned int i = 16; i < 64; i++)
	{
		s0 = RIGHTROTATE(w[i - 15], 7) ^ RIGHTROTATE(w[i - 15], 18) ^ RIGHTSHIFT(w[i - 15], 3);
		s1 = RIGHTROTATE(w[i - 2], 17) ^ RIGHTROTATE(w[i - 2], 19) ^ RIGHTSHIFT(w[i - 2], 10);
		w[i] = w[i - 16] + s0 + w[i - 7] + s1;
	}

	return w;
}
