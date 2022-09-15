#if !defined(MACRO)
#define MACRO
#define RIGHTROTATE(uint, num) ((uint >> num) | (uint << 32 - num))
#define RIGHTSHIFT(uint, num) (uint >> num)
unsigned int *h_init();
unsigned int *k_init();
unsigned int *w_init(char *text);
unsigned int *compression(char *text);
#endif // MACRO
