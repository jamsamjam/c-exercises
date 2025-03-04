# include <stdio.h>
# include <math.h>

int main(void)
{
    int n;
    int D = -1;

    printf("Enter an integer: ");
    scanf("%d", &n);

    if (n == 1) {
        printf("1 is neither prime nor composite");
        return 0;
    }    

    if (n % 2 == 0 && n != 2) {
        D = 2;
    } else {
        for (int i = 3; i <= sqrt(n); i += 2) {
            if (n % i == 0) {
                D = i;
                break;
            }
        }
    }

    D == -1
    ? printf("I strongly believe that this number is prime")
    : printf("The number is not prime, because it is divisible by %d", D); 

    return 0;
}
