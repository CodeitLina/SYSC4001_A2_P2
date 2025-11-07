#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>

int main() {
    /* the size (in bytes) of shared memory object */
    const int SIZE = 4096;     
    /* name of the shared memory object */
    const char *name = "OS"; 
    /* shared memory file descriptor */
    int shm_fd; 
    /* pointer to shared memory obect */
    int *sh;   

    // Create the shared memory object
    shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);
    ftruncate(shm_fd, SIZE);

    // Map shared memory into the process address space
    sh = (int *)mmap(0, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);

    // Two shared variables: multiple and counter
    sh[0] = 3;  // multiple 
    sh[1] = 0;  // counter

    if (fork() == 0) {
        execl("./q4p2", "q4p2", NULL);
        exit(1);
    }

    // Process 1 increments and displays until counter > 500
    while (sh[1] <= 500) {
        if (sh[1] % sh[0] == 0)
            printf("Process1: %d (multiple of %d)\n", sh[1], sh[0]);
        else
            printf("Process1: %d\n", sh[1]);
        sh[1]++;
        sleep(1);
    }

    printf("Process1 finished.\n");

    // unmap and unlink shared memory bc shmdt and shmctl are for SysV shared memory
    munmap(sh, SIZE);
    shm_unlink(name);
    return 0;
}