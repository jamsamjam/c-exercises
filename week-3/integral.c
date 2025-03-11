#include <stdio.h>
#include <math.h>

double f1(double x)
{
    return x * x;
}

double f2(double x)
{
    return sqrt(cos(x) + M_PI);
}

double f3(double x)
{
    return log(1 + sin(x));
}

typedef double (*Function)(double);

typedef struct {
    const char *name;
    Function f;
} Choice;

int get_int(const char *prompt, int min, int max) {
    int value;
    while (1) {
        printf("%s", prompt);
        if (scanf("%d", &value) == 1 && value >= min && value <= max) {
            return value;
        }
        printf("Invalid input. Please enter a number between %d and %d.\n", min, max);
        while (getchar() != '\n');
    }
}

int get_double(const char *prompt, double *value) {
    while (1) {
        printf("%s", prompt);
        if (scanf("%lf", value) == 1) {
            return 1;
        }
        printf("Invalid input. Please enter a valid number.\n");
        while (getchar() != '\n');
    }
}


Function request_function(int *n)
{
    int option = get_int(
            "You can choose from the following functions:\n"
            "   1- x square\n"
            "   2- root of (cos + pi)\n"
            "   3- log(1 + sin(x))\n"
            "   4- sin\n"
            "   5- exponential\n"
            "Which function [1-5] do you want to calculate the integral of? ", 1, 5);

    *n = option;

    Function functions[] = {f1, f2, f3, sin, exp};
    return functions[option - 1];
}

void check(double *a, double *b) {
    if (*a > *b) {
        printf("Swapping lower and upper bounds!\n");
        double temp = *a;
        *a = *b;
        *b = temp;
    }
}

double integrate(Function f, double a, double b)
{
    if (a == b) {
        return 0.0;
    }

    double res = 
        41.0*(f(a) + f(b))
        + 216.0*(f((5*a+b)/6.0) + f((5*b+a)/6.0))
        + 27.0*(f((2*a+b)/3.0) + f((2*b+a)/3.0))
        + 272.0*f((a+b)/2.0);

    return res * (b - a) / 840.0;
}

int main(void)
{
    Choice choice[] = {
        {"xˆ2" , f1},
        {"sqrt(cos + pi)" , f2},
        {"log(1 + sin())", f3},
        {"sin", sin},
        {"exp()", exp}
    };

    double a, b;
    int n = 0;
    Function f = request_function(&n);

    get_double("Enter the lower bound of the limit: ", &a);
    get_double("Enter the upper bound of the limit: ", &b);

    check(&a, &b);
    double res = integrate(f, a, b);

    printf("%s integral between %lf and %lf: %lf\n", choice[n - 1].name, a, b, res);

    return 0;
}
