#include <stdio.h>

int main(void)
{
    FILE *fp;
    char name[1024];
    int age;

    unsigned int num = 0;
    unsigned int min = (unsigned int) -1; // 'UNIT_MAX'
    unsigned int max = 0;

    double sum = 0.0;

    fp = fopen("data.dat", "r");

    if (fp == NULL) {
        printf("File read error!");
        return 1;
    }

    printf("+-----------------+-----+\n");

    while (fscanf(fp, "%s %d", name, &age) != EOF) {
        printf("| %-15s | %3d |\n", name, age);
        if (age < min) min = age;
        if (age > max) max = age;

        sum += age;
        num++;
    }

    fclose(fp);

    printf("+-----------------+-----+\n");

    printf("  minimum age     : %3d\n", min);
    printf("  maximum age     : %3d\n", max);
    printf("%d people, average age: %5.1f years\n", num, sum / num);

    return 0;
}
