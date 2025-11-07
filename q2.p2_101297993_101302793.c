#include <stdio.h>
#include <unistd.h>

int main() {
    int cycle = 0;

    while (1) {
        if (cycle % 3 == 0)
            printf("[Process2] Cycle number: %d - %d is a multiple of 3\n", cycle, cycle);
        else
            printf("[Process2] Cycle number: %d\n", cycle);

        cycle--;
        sleep(1); // delay
    }
    return 0;
}