#include <stdio.h>
#include <time.h>

int main(void)
{
    for (int i = 10; i >= 0; i--) {
        printf("\rT minus %d second%s... \b", i, i != 1 ? "s" : "");
        fflush(stdout);

        struct timespec ts = {.tv_sec = 1, .tv_nsec = 0};
        nanosleep(&ts, NULL);
    }

    printf("\rLiftoff!             \n");
    return 0;
}
