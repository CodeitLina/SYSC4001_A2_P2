#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

int main() {
    // matching process 1 (q4p1)
    const int SIZE = 4096;
    const char *name = "OS";
    int shm_fd;
    int *sh;

    // Open existing shared memory
    shm_fd = shm_open(name, O_RDWR, 0666);
    sh = (int *)mmap(0, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);

    // Wait until counter > 100
    while (sh[1] <= 100) ;

    // Print values until counter > 500
    while (sh[1] <= 500) {
        if (sh[1] % sh[0] == 0)
            printf("Process2: %d (multiple of %d)\n", sh[1], sh[0]);
        else
            printf("Process2: %d\n", sh[1]);
        sleep(1);
    }

    printf("Process2 finished.\n");

    munmap(sh, SIZE);
    return 0;
}