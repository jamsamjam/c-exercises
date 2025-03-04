#include <stdio.h>
#include <math.h>

double f(double x)
{
    return x * x;
}

double integrate(double a, double b)
{
    double res = 
        41.0*(f(a) + f(b))
        + 216.0*(f((5*a+b)/6.0) + f((5*b+a)/6.0))
        + 27.0*(f((2*a+b)/3.0) + f((2*b+a)/3.0))
        + 272.0*f((a+b)/2.0);

    return res * (b - a) / 840.0;
}

int main(void)
{
    double a, b;

    printf("Enter the lower bound of the limit: ");
    scanf("%lf", &a);
    printf("Enter the upper bound of the limit: ");
    scanf("%lf", &b);

    double res = integrate(a, b);
    printf("Calculated value is.. %lf", res);

    return 0;
}
