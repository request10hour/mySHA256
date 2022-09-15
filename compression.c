#include "mysha256.h"
#include "utils/myutils.h"

static void comp_sub(unsigned int *k, unsigned int *w, unsigned int *comp, unsigned int i)
{
	unsigned int s1, ch, temp1, s0, maj, temp2;
	s1 = RIGHTROTATE(comp[4], 6) ^ RIGHTROTATE(comp[4], 11) ^ RIGHTROTATE(comp[4], 25);
	ch = (comp[4] & comp[5]) ^ ((~comp[4]) & comp[6]);
	temp1 = comp[7] + s1 + ch + k[i] + w[i];
	s0 = RIGHTROTATE(comp[0], 2) ^ RIGHTROTATE(comp[0], 13) ^ RIGHTROTATE(comp[0], 22);
	maj = (comp[0] & comp[1]) ^ (comp[0] & comp[2]) ^ (comp[1] & comp[2]);
	temp2 = s0 + maj;

	comp[7] = comp[6];
	comp[6] = comp[5];
	comp[5] = comp[4];
	comp[4] = comp[3] + temp1;
	comp[3] = comp[2];
	comp[2] = comp[1];
	comp[1] = comp[0];
	comp[0] = temp1 + temp2;
}

unsigned int *compression(char *text)
{
	unsigned int *h = h_init();
	unsigned int *k = k_init();
	unsigned int *w = w_init(text);
	static unsigned int comp[8];
	my_memmove(comp, h, 32);
	for (unsigned int i = 0; i < 64; i++)
		comp_sub(k, w, comp, i);
	return comp;
}

// #include <stdio.h>
// int main(int argc, char **argv)
// {
// 	unsigned int *h = h_init();
// 	unsigned int *comp = compression(argv[1]);
// 	for (size_t i = 0; i < 8; i++)
// 		printf("%08x", h[i] + comp[i]);
// 	printf("\n");
// 	return 0;
// }
