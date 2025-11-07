#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();

    if (pid == 0) {
        execl("./q3p2", "q3p2", NULL);
        perror("exec failed");
        exit(1);
    }

    printf("Process1: waiting for Process2 to finish...\n");
    wait(NULL);
    printf("Process1: Process2 finished. Exiting.\n");
    return 0;
}