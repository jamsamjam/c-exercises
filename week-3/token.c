#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_SIZE 1024

int nextToken(char const *str, size_t *from, size_t *len);

int main(void)
{
    char phrase[MAX_SIZE + 1];

    printf("Enter a string: ");
    if (fgets(phrase, MAX_SIZE + 1, stdin) == NULL) {
        return 1;
    }

    if (phrase[0] != '\0') {
        if (phrase[strlen(phrase) - 1] == '\n') phrase[strlen(phrase) - 1] = '\0';
    }

    size_t from = 0;
    size_t length = 0;
    printf("The words of \"%s\" are:\n", phrase);
    while (nextToken(phrase, &from, &length)) {
        char word[MAX_SIZE + 1];

        strncpy(word, &(phrase[from]), length);

        word[length] = '\0'; // needed to use `%s`
        printf("'%s'\n", word);

        from += length;
    }
    return 0;
}

int nextToken(char const *str, size_t *from, size_t *len)
{
    if (*str == '\0') return 2;

    const size_t size = strlen(str);

    while (*from < size && isspace(str[*from])) {
        (*from)++;
    }

    if (*from >= size) {
        return 0;
    }

    *len = 0;
    
    // The following code does not use <ctype.h> and does not parse special characters separately.

    // while ((*from + *len) < size && str[*from + *len] != ' ') {
    //     (*len)++;
    // }

    if (ispunct(str[*from])) {
        *len = 1;
    } else {
        while ((*from + *len) < size && !isspace(str[*from + *len]) && !ispunct(str[*from + *len])) {
            (*len)++;
        }
    }

    return 1;
}