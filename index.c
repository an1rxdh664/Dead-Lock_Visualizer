#include <stdio.h>

int main() {
    int p, r;
    printf("Enter the number of processes: ");
    scanf("%d", &p);

    printf("Enter the number of resources: ");
    scanf("%d", &r);

    int allocated[p][r], max[p][r], need[p][r], total[r], available[r];
    int finish[p], safeSeq[p];
    int count = 0;

    printf("Enter allocation matrix:\n");
    for (int i = 0; i < p; i++) {
        printf("Enter resources allocated to P%d : \n",i+1);
        for (int j = 0; j < r; j++) {
            printf("Enter R%d : ",j+1);
            scanf("%d", &allocated[i][j]);
        }
    }

    printf("Enter maximum matrix:\n");
    for (int i = 0; i < p; i++) {
        printf("Enter maximum resources required by P%d : \n",i+1);
        for (int j = 0; j < r; j++) {
            printf("Enter R%d : ",j+1);
            scanf("%d", &max[i][j]);
        }
    }

    printf("Enter total resources:\n");
    for (int i = 0; i < r; i++) {
        printf("Enter total resources for R%d : ",i+1);
        scanf("%d", &total[i]);
    }

    for (int i = 0; i < p; i++) {
        for (int j = 0; j < r; j++) {
            need[i][j] = max[i][j] - allocated[i][j];
        }
    }

    for (int j = 0; j < r; j++) {
        available[j] = total[j];
        for (int i = 0; i < p; i++) {
            available[j] -= allocated[i][j];
        }
    }

    for (int i = 0; i < p; i++) {
        finish[i] = 0;
    }

    printf("Allocation matrix : \n");
    for(int i=0;i<p;i++){
        for(int j=0;j<r;j++){
            printf("%d ",allocated[i][j]);
        } printf("\n");
    }
    printf("Maximum Resource Needed matrix : \n");
    for(int i=0;i<p;i++){
        for(int j=0;j<r;j++){
            printf("%d ",max[i][j]);
        } printf("\n");
    }
    printf("Total resources in the system : \n");
    for(int i=0;i<r;i++){
        printf("%d ", total[i]);
    }
    printf("\nAvailable Resources in the system : \n");
    for(int i=0;i<r;i++){
        printf("%d ", available[i]);
    }
    printf("\nNeed matrix : \n");
    for(int i=0;i<p;i++){
        for(int j=0;j<r;j++){
            printf("%d ", need[i][j]);
        } printf("\n");
    }

    while (count < p) {
        int safe = 0;
        for (int i = 0; i < p; i++) {
            if (finish[i] == 0) {
                int flag = 1;
                for (int j = 0; j < r; j++) {
                    if (need[i][j] > available[j]) {
                        flag = 0;
                        break;
                    }
                }

                if (flag == 1) {
                    for (int j = 0; j < r; j++) {
                        available[j] += allocated[i][j];
                    }
                    safeSeq[count++] = i;
                    finish[i] = 1;
                    safe = 1;
                }
            }
        }

        if (safe == 0) {
            break;
        }
    }

    if (count == p) {
        printf("\nSystem is in a safe state.\nSafe Sequence: ");
        for (int i = 0; i < p; i++) {
            printf("P%d ", safeSeq[i]);
        }
        printf("\n");
    } else {
        printf("\nSystem is NOT in a safe state.Deadlock Detected!\n");
    }

    return 0;
}