#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <semaphore.h>

int main() {
    // same as p1
    const int   SIZE     = 4096;
    const char *shm_name = "OS";
    const char *sem_name = "OS_MUTEX";

    // open existing shared memory and map it 
    int  shm_fd = shm_open(shm_name, O_RDWR, 0666);
    int *sh     = (int *)mmap(0, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);

    // open the existing semaphore that is created by Process 1
    sem_t *sem  = sem_open(sem_name, 0);

    // wait until the shared counter becomes > 100 because reading are guarded 
    while (1) {
        int c;
        sem_wait(sem);
        c = sh[1];
        sem_post(sem);
        if (c > 100) break;
    }

    /* once started print identity + value until counter > 500 */
    while (1) {
        int c, m, done;

        sem_wait(sem);
        m    = sh[0];
        c    = sh[1];
        done = (c > 500);
        sem_post(sem);

        if (done) break;

        if (c % m == 0)
            printf("Process2: %d (multiple of %d)\n", c, m);
        else
            printf("Process2: %d\n", c);

        sleep(1);
    }

    printf("Process2 finished.\n");

    // detach because the parent does the unlinking
    munmap(sh, SIZE);
    return 0;
}