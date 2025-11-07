#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <semaphore.h>

int main() {
    // following question 4 
    const int SIZE = 4096;
    const char *shm_name  = "OS";        
    const char *sem_name  = "/OS_MUTEX";  
    int shm_fd;
    int *sh;

    // create/open the shared memory object 
    shm_fd = shm_open(shm_name, O_CREAT | O_RDWR, 0666);
    ftruncate(shm_fd, SIZE); // size the new object so mmap won’t segfault 
    sh = (int *)mmap(0, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);

    /* create/open a named semaphore to protect the shared memory */
    //initial value = 1 = unlocked (acts like a simple mutex)   
    sem_t *sem = sem_open(sem_name, O_CREAT, 0666, 1);

    // initialize the two shared integers under the lock
    sem_wait(sem);
    sh[0] = 3;   // multiple 
    sh[1] = 0;   // counter  
    sem_post(sem);

    
    if (fork() == 0) {
        execl("./q5p2", "q5p2", NULL);
        exit(1); 
    }

    // Process 1 loop: increment + print until counter > 500 
    while (1) {
        int m, c, done;

        /* lock 
        read/modify 
        unlock (critical section) 
        */
        sem_wait(sem);
        m = sh[0];
        c = sh[1];

        if (c % m == 0)
            printf("Process1: %d (multiple of %d)\n", c, m);
        else
            printf("Process1: %d\n", c);

        sh[1] = c + 1;/* increment shared counter */
        done  = (sh[1] > 500);/* check stop condition inside lock */
        sem_post(sem);

        if (done) break;
        sleep(1);              
    }

    printf("Process1 finished.\n");

    //close/unlink semaphore, unmap/unlink shared memory 
    sem_close(sem);
    sem_unlink(sem_name);

    munmap(sh, SIZE);
    shm_unlink(shm_name);

    return 0;
}