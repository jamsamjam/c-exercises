#include <stdio.h>

typedef struct {
    double re, im;
} Complexe;

void display(Complexe n);
Complexe add(Complexe a, Complexe b);
Complexe subtract(Complexe a, Complexe b);
Complexe multiply(Complexe a, Complexe b);
Complexe divide(Complexe a, Complexe b);

int main(void)
{
    Complexe c1 = {.re = 1.0, .im = 0.0};
    Complexe c2 = {.re = 0.0, .im = 1.0};
    Complexe c3 = {.re = 1.0, .im = 1.0};
    Complexe c4 = {.re = 0.0, .im = 2.0};
    Complexe c5 = {.re = 2.0, .im = -3.0};

    display(add(c1, c2)); // 1, 1
    display(multiply(c2, c2)); // -1, 0
    display(multiply(c3, c3)); // 0, 2
    display(divide(c4, c2)); // 2, 0
    display(divide(c5, c3)); // -0.5, -2.5)

    return 0;
}

void display(Complexe n)
{
    printf("%lf + %lfi\n", n.re, n.im);
}

Complexe add(Complexe a, Complexe b)
{
    Complexe res = {.re = a.re + b.re, .im = a.im + b.im};
    return res;
}

Complexe subtract(Complexe a, Complexe b)
{
    Complexe res = {.re = a.re - b.re, .im = a.im - b.im};
    return res;
}

Complexe multiply(Complexe a, Complexe b)
{
    Complexe res = {.re = a.re * b.re - a.im * b.im,
        .im = a.re * b.im + a.im * b.re};
    return res;
}

Complexe divide(Complexe a, Complexe b)
{
    Complexe res = {.re = (a.re * b.re + a.im * b.im) / (b.re * b.re + b.im * b.im),
        .im = (a.im * b.re - a.re * b.im) / (b.re * b.re + b.im * b.im)};
    return res;
}

