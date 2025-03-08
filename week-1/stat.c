#include <stdio.h>
#include <string.h>

#define MAX_ELEMENTS 256

typedef unsigned long int Statistics[MAX_ELEMENTS];

FILE* request_file();
void initialize_statistics(Statistics stats);
unsigned long int collect_statistics(Statistics to_be_filled, FILE* file_to_read);
void display(Statistics stat);

int main(void)
{
    FILE *fp = request_file();
    if (fp == NULL) return 1;

    Statistics stat;
    collect_statistics(stat, fp);
    
    display(stat);
    fclose(fp);

    return 0;
}

FILE* request_file()
{
    FILE *fp;
    char name[MAX_ELEMENTS];

    for (int i = 0; i < 3; i++) {
        printf("Enter the name of the file to read: ");
        fflush(stdout);
        // scanf("%s", name);
        fgets(name, sizeof(name), stdin);
        name[strcspn(name, "\n")] = '\0'; 

        fp = fopen(name, "r");

        if (fp != NULL) {
            printf(" -> OK, \"%s\" file opened for reading.", name);
            return fp;
        }

        printf(" -> ERROR, I cannot read the file \"%s\"\n", name);
    }

    printf("=> I give up!");
    return NULL;
}

void initialize_statistics(Statistics stats)
{
    for (int i = 0; i < MAX_ELEMENTS; i++) {
        stats[i] = 0;
    }
}

unsigned long int collect_statistics(Statistics to_be_filled, FILE* file_to_read)
{
    char c;
    unsigned long int n = 0;

    initialize_statistics(to_be_filled);

    while ((c = getc(file_to_read)) != EOF) {
        if ((unsigned char) c >= 32 && (unsigned char) c <= 253) {
            // [0] 32, [221 = 253-32] 253
            to_be_filled[c - 32]++;
            n++;
        }
    }

    return n;
}

void display(Statistics stat)
{
    // int size = sizeof(Statistics) / sizeof(stat[0]);
    unsigned long int count = 0;

    printf("STATISTICS: \n");
    fflush(stdout);

    for (int i = 0; i < MAX_ELEMENTS; i++) {
        if (stat[i] > 0)
            count += stat[i];
    }  

    for (int i = 0; i < MAX_ELEMENTS; i++) {
        if (stat[i] > 0)
            printf("%c: %11lu - %5.2lf%%\n", (char) i + 32, stat[i], 100.0 * stat[i] / (double) count);
    }  
}