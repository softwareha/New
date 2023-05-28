#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int pid;      
    int bTime; 
    int wTime; 
    int tTime; 
} P;
void calculateTimes(P p[], int n) {
    int totalwt = 0;
    int totaltt = 0;

    processes[0].waitingTime = 0; 
    for (int i = 1; i < n; i++) {
        p[i].wTime = p[i - 1].wTime + p[i - 1].bTime;
        p[i].tTime = p[i].wTime + p[i].bTime;

        totalwt += p[i].wTime;
        totaltt += p[i].tTime;
    }

    float avgwt = (float)totalwt / n;

    printf("\nProcess\tBurst Time\tWaiting Time\tTurnaround Time\n");

    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\n", p[i].pid, p[i].bTime, p[i].wTime, p[i].tTime);
    }

    printf("\nAverage Waiting Time: %.2f\n", avgwt);
}

void fcfsScheduling(P p[], int n) {
    calculateTimes(p, n);
}


void sjfScheduling(P p[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < n; j++) {
            if (p[j].bTime < p[minIndex].bTime) {
                minIndex = j;
            }
        }

        P temp = p[minIndex];
        p[minIndex] = p[i];
        p[i] = temp;
    }

    calculateTimes(p, n);
}
void rrScheduling(P p[], int n, int quantum) {

    int* remainingTime = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        remainingTime[i] = p[i].bTime;
    }

    int t = 0; 
    while (1) {
        int done = 1;
        for (int i = 0; i < n; i++) {
            if (remainingTime[i] > 0) {
                done = 0; 
                if (remainingTime[i] > quantum) {
                    t += quantum;
                    remainingTime[i] -= quantum;
                }
                else {
                    t += remainingTime[i];
                    p[i].waitingTime = t - p[i].bTime;
                    remainingTime[i] = 0;
                }
            }
        }

        if (done) {
            break; 
        }
    }

    calculateTimes(processes, n);
    free(remainingTime);
}

int main() {
    int n; 

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    P* p = (P*)malloc(n * sizeof(P));
    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("Enter burst time for process %d: ", i + 1);
        scanf("%d", &p[i].bTime);
    }

    int choice;
    printf("\nCPU Scheduling Algorithms:\n");
    printf("1. First-Come, First-Served (FCFS)\n");
    printf("2. Shortest Job First (SJF)\n");
    printf("3. Round Robin (RR)\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            fcfsScheduling(p, n);
            break;
        case 2:
            sjfScheduling(p, n);
            break;
        case 3:
            {
                int quantum;
                printf("Enter the time quantum for Round Robin: ");
                scanf("%d", &quantum);
                rrScheduling(p, n, quantum);
            }
            break;
        default:
            printf("Invalid choice.\n");
            break;
    }

    free(p);

    return 0;
}

