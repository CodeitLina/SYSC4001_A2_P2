#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    int cycle = 0;
    pid_t pid;

    // Create a new process using fork
    pid = fork();  

    if (pid == 0) {
        execl("./q2p2", "q2p2", NULL); // run process2
        perror("exec failed");
        exit(1);
    }

    while (1) {
        if (cycle % 3 == 0)
            printf("Cycle number: %d - %d is a multiple of 3\n", cycle, cycle);
        else
            printf("Cycle number: %d\n", cycle);

        cycle++;
        sleep(1); // delay
    }
    return 0;
}