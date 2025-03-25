#include <stdio.h>
#include <stdbool.h>

#define P 3 // Number of processes
#define R 3 // Number of resources

int main() {
    int allocation[P][R] = { {0, 1, 0}, {2, 0, 0}, {3, 0, 2} }; // Allocated resources
    int max[P][R] = { {7, 5, 3}, {3, 2, 2}, {9, 0, 2} }; // Maximum demand
    int available[R] = {3, 3, 2}; // Available resources

    int need[P][R]; // Remaining need of each process
    bool finish[P] = {false}; // To track completed processes
    int work[R]; // Temporary work array for available resources
    int i, j, p, count = 0;

    // Calculate NEED matrix (Max - Allocation)
    for (i = 0; i < P; i++) {
        for (j = 0; j < R; j++) {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }

    // Copy available resources into work array
    for (i = 0; i < R; i++) {
        work[i] = available[i];
    }

    // Deadlock Detection using Safety Algorithm (Simplified Banker's Algorithm)
    while (count < P) {
        bool found = false;
        for (p = 0; p < P; p++) {
            if (!finish[p]) { // If process is not finished
                bool canAllocate = true;
                for (j = 0; j < R; j++) {
                    if (need[p][j] > work[j]) {
                        canAllocate = false;
                        break;
                    }
                }
                if (canAllocate) {
                    // Simulate allocation
                    for (j = 0; j < R; j++) {
                        work[j] += allocation[p][j];
                    }
                    finish[p] = true;
                    count++;
                    found = true;
                }
            }
        }
        if (!found) {
            printf("Deadlock detected!\n");
            return 1;
        }
    }

    printf("No Deadlock! System is in a safe state.\n");
    return 0;
}