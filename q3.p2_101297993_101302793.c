#include <stdio.h>
#include <unistd.h>

int main() {
    int cycle = 0;

    while (cycle > -500) {
        if (cycle % 3 == 0)
            printf("[Process2] Cycle number: %d - %d is a multiple of 3\n", cycle, cycle);
        else
            printf("[Process2] Cycle number: %d\n", cycle);

        cycle--;
        //sleep(1); commented out to speed up execution
    }

    printf("[Process2] Reached below -500. Exiting.\n");
    return 0;
}