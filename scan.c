#include <stdio.h>
#include <stdlib.h>

#define MAX 100

void scan(int disk_queue[], int disk_size, int head_pos, int direction) {
    int i, j, seek_time = 0;
    int seek_sequence[MAX];
    int total_seeks = 0;

    int current_pos = head_pos;
    int max_cylinder = disk_size - 1;
    int min_cylinder = 0;

    printf("Disk Scheduling Order: ");

    if (direction == 1) {
        // Moving towards higher cylinder numbers
        for (i = current_pos; i <= max_cylinder; i++) {
            printf("%d ", i);
            seek_sequence[total_seeks++] = i;
        }

        // Move to the rightmost cylinder
        seek_time += abs(max_cylinder - current_pos);
        current_pos = max_cylinder;

        // Start moving towards lower cylinder numbers
        printf("%d ", current_pos);
        seek_sequence[total_seeks++] = current_pos;

        for (i = current_pos - 1; i >= min_cylinder; i--) {
            printf("%d ", i);
            seek_sequence[total_seeks++] = i;
        }
    } else {
        // Moving towards lower cylinder numbers
        for (i = current_pos; i >= min_cylinder; i--) {
            printf("%d ", i);
            seek_sequence[total_seeks++] = i;
        }

        // Move to the leftmost cylinder
        seek_time += abs(current_pos - min_cylinder);
        current_pos = min_cylinder;

        // Start moving towards higher cylinder numbers
        printf("%d ", current_pos);
        seek_sequence[total_seeks++] = current_pos;

        for (i = current_pos + 1; i <= max_cylinder; i++) {
            printf("%d ", i);
            seek_sequence[total_seeks++] = i;
        }
    }

    printf("\nTotal Seek Time: %d\n", seek_time);

    // Calculate average seek time
    float avg_seek_time = (float) seek_time / total_seeks;
    printf("Average Seek Time: %.2f\n", avg_seek_time);
}

int main() {
    int disk_queue[MAX];
    int disk_size, head_pos, direction;
    int i;

    printf("Enter the number of cylinders in the disk: ");
    scanf("%d", &disk_size);

    printf("Enter the initial position of disk head: ");
    scanf("%d", &head_pos);

    printf("Enter the direction (1 for towards higher cylinder numbers, 0 for towards lower cylinder numbers): ");
    scanf("%d", &direction);

    printf("Enter the disk queue:\n");
    for (i = 0; i < disk_size; i++) {
        scanf("%d", &disk_queue[i]);
    }

    scan(disk_queue, disk_size, head_pos, direction);

    return 0;
}
