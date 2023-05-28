#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX 100

int abs_diff(int a, int b) {
    return (a > b) ? (a - b) : (b - a);
}

int find_closest(int disk_queue[], int disk_size, int head_pos, int visited[]) {
    int min_diff = INT_MAX;
    int closest_index = -1;

    for (int i = 0; i < disk_size; i++) {
        if (!visited[i]) {
            int diff = abs_diff(disk_queue[i], head_pos);
            if (diff < min_diff) {
                min_diff = diff;
                closest_index = i;
            }
        }
    }

    return closest_index;
}

void sstf(int disk_queue[], int disk_size, int head_pos) {
    int visited[MAX] = {0};
    int seek_time = 0;
    int seek_sequence[MAX];
    int total_seeks = 0;

    int current_pos = head_pos;

    printf("Disk Scheduling Order: ");

    for (int i = 0; i < disk_size; i++) {
        int closest_index = find_closest(disk_queue, disk_size, current_pos, visited);
        visited[closest_index] = 1;

        seek_time += abs_diff(current_pos, disk_queue[closest_index]);
        current_pos = disk_queue[closest_index];

        printf("%d ", current_pos);
        seek_sequence[total_seeks++] = current_pos;
    }

    printf("\nTotal Seek Time: %d\n", seek_time);

    // Calculate average seek time
    float avg_seek_time = (float) seek_time / total_seeks;
    printf("Average Seek Time: %.2f\n", avg_seek_time);
}

int main() {
    int disk_queue[MAX];
    int disk_size, head_pos;
    int i;

    printf("Enter the number of cylinders in the disk: ");
    scanf("%d", &disk_size);

    printf("Enter the initial position of disk head: ");
    scanf("%d", &head_pos);

    printf("Enter the disk queue:\n");
    for (i = 0; i < disk_size; i++) {
        scanf("%d", &disk_queue[i]);
    }

    sstf(disk_queue, disk_size, head_pos);

    return 0;
}
