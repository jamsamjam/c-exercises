#include <stdio.h>
#include <string.h>

typedef void (*Cmd)(void *data);

void print(void *data);
void add(void *data);
void push(void *data);
void pop(void *data);
void quit(void *data);

Cmd interpreter(const char *data);

int main(void)
{
    double array[2] = {0.0, 0.0}; // 2-register memory

    Cmd cmd = quit;
    do {
        char read[] = "blabla";
        printf("Enter a command (print, add, push, pop, quit) : ");
        scanf("%s", read);
        (cmd = interpreter(read))(array);
    } while (cmd != quit);

    return 0;
}

void print(void *data)
{
    const double *const p = data;
    printf("-> %lf\n", *p);
}

void add(void *data)
{
    double *const p = data;
    p[0] += p[1];
}

void push(void *data)
{
    double *const p = data;
    p[1] = p[0];
    
    printf("Value ? ");
    if (scanf("%lf", p) != 1) {
        printf("Invalid input.\n");
        while (getchar() != '\n');
    }
}

void pop(void *data)
{
    double *const p = data;
    p[0] = p[1];
}

void quit(void *data)
{
    printf("Bye!");
}

Cmd interpreter(const char *name)
{
    if (name == NULL) return quit;

    if (!strcmp(name, "print")) {
        return print;
    } else if (!strcmp(name, "add")) {
        return add;
    } else if (!strcmp(name, "push")) {
        return push;
    } else if (!strcmp(name, "pop")) {
        return pop;
    }
    return quit;
}