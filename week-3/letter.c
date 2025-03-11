#include <stdio.h>

typedef enum {Male, Female} Gender;

void generateLetter(Gender gender,
    const char *receiver,
    const char *title,
    unsigned int day,
    unsigned int month,
    const char *closing,
    const char *sender)
{
    printf("Dear %s %s,\n", gender == Male ? "Mr." : "Ms.", receiver);
    printf("I am writing to you regarding %s.\n", title);
    printf("We should see each other on %d/%d to discuss it.\n", day, month);
    printf("Let me know!\n");
    printf("%s, %s.\n", closing, sender);
}

int main(void)
{
    generateLetter(Male, "John", "our love", 10, 10, "Love", "Merry");
    generateLetter(Female, "Merry", "our project", 9, 10, "Sincerely", "John");
    return 0;
}

