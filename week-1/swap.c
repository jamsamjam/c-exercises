#include <stdio.h>

void swap(int* i, int* j) 
{
    int temp = *i;
    *i = *j;
    *j = temp;
}

int main(void)
{
    int i = 10;
    int j = 55;

    printf("Before: i=%d and j=%d\n", i, j);
    swap(&i, &j);

    printf("After: i=%d and j=%d\n", i, j);
    return 0;
}
