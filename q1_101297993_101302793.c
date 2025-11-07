#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>  
#include <stdlib.h>

int main(void) {
    pid_t pid; 

    // Create a new process using fork
    pid= fork();  

    if (pid < 0) {
        perror("fork failed");
        exit(1);
    }

    if (pid == 0) {
        // Child process (Process 2)
        int counter = 0;
        printf("Process 2 started, PID = %d\n", getpid());
        while (1) {
            printf("Process 2 counter: %d\n", counter++);
            sleep(1); // Sleep for 1 second
        }
    } else {
        // Parent process (Process 1)
        int counter = 0;
        printf("Process 1 started, PID = %d\n", getpid());
        while (1) {
            printf("Process 1 counter: %d\n", counter++);
            sleep(1); // Sleep for 1 second
        }
    }

    return 0;
}

