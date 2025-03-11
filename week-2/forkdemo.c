#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc __attribute__((unused)),
         char *argv[])
{
    printf("Hello world, I'm PID: %d (%s)\n", (int) getpid(), argv[0]);

    pid_t pid = fork();
    if (pid < 0) {
        // fork failed
        fprintf(stderr, "fork failed\n");
        exit(1);

    } else if (pid == 0) {
        // child (new) process
        printf("Hello, I am child (pid: %d)\n", (int) getpid());
        char *myargs[3] = {
            strdup("wc"),         // program: “wc” (word count)
            strdup("forkdemo.c"), // argument: file to count
            NULL                  // marks end of the array
        };
        execvp(myargs[0], myargs);    // runs word count program
        puts("This should be never printed");

    } else {
        // Parent process execution path
        pid_t wc = wait(NULL);
        printf("Hello, I am a parent of %d (wc: %d) (pid: %d)\n",
               pid, wc, (int) getpid());
    }
    return 0;
}