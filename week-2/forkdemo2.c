#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>

#define OUTPUT "wc-output.txt"

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
        // child: redirect standard output to a file
        printf("Hello, I am child (pid: %d), will write to " OUTPUT "\n",
               (int) getpid());
        close(STDOUT_FILENO);
        (void)open(OUTPUT, O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
        char *myargs[3] = {
            strdup("wc"),          // program: “wc” (word count)
            strdup("forkdemo2.c"), // argument: file to count
            NULL                   // marks end of the array
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