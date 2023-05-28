#include <stdio.h>
#include <stdlib.h>

int abs(int a) {
    return (a < 0) ? -a : a;
}

int main() {
    int numRequests;   // Number of disk requests
    int headPosition;  // Initial position of the disk head

    printf("Enter the number of disk requests: ");
    scanf("%d", &numRequests);

    int requests[numRequests];  // Array to store the disk requests

    printf("Enter the disk requests:\n");
    for (int i = 0; i < numRequests; i++) {
        printf("Request %d: ", i + 1);
        scanf("%d", &requests[i]);
    }

    printf("Enter the initial position of the disk head: ");
    scanf("%d", &headPosition);

    int totalMovement = 0;  // Total head movement
    int currentTrack = headPosition;

    printf("\n--- Disk Scheduling Algorithm: FCFS ---\n");
    printf("Head Position\t\tMovement\n");

    for (int i = 0; i < numRequests; i++) {
        int movement = abs(requests[i] - currentTrack);
        totalMovement += movement;
        currentTrack = requests[i];
        printf("%d\t\t\t%d\n", currentTrack, movement);
    }

    printf("\nTotal Head Movement: %d\n", totalMovement);

    return 0;
}

