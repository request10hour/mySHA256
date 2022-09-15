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
