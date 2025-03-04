#include <stdio.h>
#include <math.h>

double const g = 9.81;

int main(void) 
{
    double H0, eps;
    int NBR;
    double v, h;

    do {
        printf("Enter the initial height(x >= 0): ");
        scanf("%lf", &H0);
    } while (H0 < 0);

    do {
        printf("Enter the rebound coefficient(0 <= x < 1): ");
        scanf("%lf", &eps);
    } while (eps < 0 || eps >= 1);

    do {
        printf("Enter the number of bounces(0 <= x): ");
        scanf("%d", &NBR);
    } while (NBR < 0);

    h = H0; // initial height

    for(int i = 0; i < NBR; i++) {
        v = sqrt(2.0 * g * h);
        v = v * eps;
        h = (v * v) / (2 * g);
    }

    printf("At the %dth bounce, the height will be %lf m.", NBR, h);
    return 0;
}


