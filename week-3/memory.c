#include <stdio.h>

typedef unsigned char byte;

void print_binary(const byte b)
{
    for (byte mask = 0x80; mask; mask >>= 1) {
        putchar((b & mask) ? '1' : '0');
    }
}

void dump_mem(const byte* p, size_t N)
{
    const byte* const end = p + N;

    for (const byte* ptr = p; ptr < end; ++ptr) {
        printf("%p : ", ptr);
        print_binary(*ptr);
        printf(" %3u ", (unsigned int) *ptr);
        if ((*ptr >= 32) && (*ptr <= 126)) {
            printf("'%c'", *ptr);
            }
        putchar('\n');
    }
    puts("------------------------------------");
}

int main(void)
{
    int a = 64 + 16;
    int b = -a;
    double c = 0.5;
    double d = 0.1;

    dump_mem((byte *)&a, sizeof(a));
    dump_mem((byte *)&b, sizeof(b));
    dump_mem((byte *)&c, sizeof(c));
    dump_mem((byte *)&d, sizeof(d));

    return 0;
}
