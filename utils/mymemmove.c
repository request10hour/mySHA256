void *my_memmove(void *dst, const void *src, unsigned int len)
{
	unsigned int i;

	if (dst == src)
		return (dst);
	if (dst > src && (unsigned int)(dst - src) < len)
	{
		i = len;
		while (i > 0)
		{
			((unsigned char *)dst)[i - 1] = ((unsigned char *)src)[i - 1];
			i--;
		}
		return (dst);
	}
	i = 0;
	while (i < len)
	{
		((unsigned char *)dst)[i] = ((unsigned char *)src)[i];
		i++;
	}
	return (dst);
}
