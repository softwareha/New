#include <stdio.h>
#include <stdlib.h>

#define MAX_BLOCKS 100   // Maximum number of blocks in the file system

void printDiskStatus(int disk[], int numBlocks) {
    for (int i = 0; i < numBlocks; i++) {
        if (disk[i] == -1)
            printf("- ");
        else
            printf("%d ", disk[i]);
    }
    printf("\n");
}

int findContiguousBlocks(int disk[], int numBlocks, int fileSize) {
    int startBlock = -1;
    int consecutiveBlocks = 0;
    for (int i = 0; i < numBlocks; i++) {
        if (disk[i] == -1) {
            if (startBlock == -1)
                startBlock = i;
            consecutiveBlocks++;
            if (consecutiveBlocks == fileSize)
                return startBlock;
        } else {
            startBlock = -1;
            consecutiveBlocks = 0;
        }
    }
    return -1;
}

void allocateFile(int disk[], int numBlocks, int startBlock, int fileSize, int fileId) {
    for (int i = startBlock; i < startBlock + fileSize; i++)
        disk[i] = fileId;
}

void deallocateFile(int disk[], int numBlocks, int fileId) {
    for (int i = 0; i < numBlocks; i++) {
        if (disk[i] == fileId)
            disk[i] = -1;
    }
}

int main() {
    int disk[MAX_BLOCKS];   // Array to represent disk blocks
    int numBlocks;          // Total number of blocks in the file system

    printf("Enter the total number of blocks in the disk: ");
    scanf("%d", &numBlocks);

    // Initialize disk blocks as empty (-1)
    for (int i = 0; i < numBlocks; i++)
        disk[i] = -1;

    int choice;
    do {
        printf("\n--- File Allocation Strategy Menu ---\n");
        printf("1. Print Disk Status\n");
        printf("2. Allocate File\n");
        printf("3. Deallocate File\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                printf("\nDisk Status:\n");
                printDiskStatus(disk, numBlocks);
                break;
            }
            case 2: {
                int fileSize, fileId;
                printf("\nEnter the file size: ");
                scanf("%d", &fileSize);
                printf("Enter the file ID: ");
                scanf("%d", &fileId);
                int startBlock = findContiguousBlocks(disk, numBlocks, fileSize);
                if (startBlock != -1) {
                    allocateFile(disk, numBlocks, startBlock, fileSize, fileId);
                    printf("\nFile allocated successfully!\n");
                } else {
                    printf("\nUnable to allocate file. Not enough contiguous blocks available.\n");
                }
                break;
            }
            case 3: {
                int fileId;
                printf("\nEnter the file ID to deallocate: ");
                scanf("%d", &fileId);
                deallocateFile(disk, numBlocks, fileId);
                printf("\nFile deallocated successfully!\n");
                break;
            }
            case 4: {
                printf("\nExiting...\n");
                break;
            }
            default: {
                printf("\nInvalid choice. Please try again.\n");
            }
        }
    } while (choice != 4);

    return 0;
}

