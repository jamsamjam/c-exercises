#include <stdio.h>
#include <math.h>

typedef struct {
    double re, im;
} Complexe;

typedef struct {
    Complexe z1, z2;
} Solutions;

void display(Complexe n);
Complexe add(Complexe a, Complexe b);
Complexe subtract(Complexe a, Complexe b);
Complexe multiply(Complexe a, Complexe b);
Complexe divide(Complexe a, Complexe b);
Complexe sroot(Complexe c);
Solutions resolve_second_degree(Complexe b, Complexe c);

int main(void)
{
    Complexe c1 = {.re = -1.0, .im = 0.0};
    // Complexe c2 = {.re = 0.0, .im = 1.0};
    // Complexe c3 = {.re = 1.0, .im = 1.0};
    // Complexe c4 = {.re = 0.0, .im = 2.0};
    // Complexe c5 = {.re = 2.0, .im = -3.0};

    display(sroot(c1));

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

int sgn(int n) 
{
    // We follow the convention where sgn(0) = 1
    return n >= 0 ? 1 : -1;
}

Complexe sroot(Complexe c) 
{
    Complexe res;

    res.re = sqrt((sqrt(c.re * c.re + c.im * c.im) + c.re) / 2);
    res.im = sgn(c.im) * sqrt((sqrt(c.re * c.re + c.im * c.im) - c.re) / 2);

    return res;
}

Solutions resolve_second_degree(Complexe b, Complexe c)
{
    // z*z + b*z + c = 0
    // Δ = b^2 - 4c
    Complexe delta = sroot(subtract(multiply(b, b), multiply((Complexe){4, 0}, c)));

    // -b
    Complexe nb = subtract((Complexe){0.0, 0.0}, b);

    // -b +- Δ / 2
   return (Solutions) {
        divide(add(nb, delta), (Complexe){2.0, 0.0}),
        divide(subtract(nb, delta), (Complexe){2.0, 0.0})
   };
}