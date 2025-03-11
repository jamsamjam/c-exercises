#include <stdio.h>

typedef unsigned char byte;

void binary_print(byte b)
{
    for (int i = 7; i >= 0; i--) {
        putchar((b & (1 << i)) ? '1' : '0');
    }
}

void display(size_t size, byte b)
{
    printf("%02zu : ", size);
    binary_print(b);
    printf("  %3u ", b);

    if (b >= 32 && b <= 126) {
        printf("\'%c\'", (char)b);
    }

    putchar('\n');
}

void dump_mem(byte* p, size_t N)
{
    printf("Starting from %p:\n", (void *)p);

    for (size_t i = 0; i < N; i++) {
        display(i, p[i]);
    }
    
    putchar('\n');
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
