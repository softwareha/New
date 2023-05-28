#include <stdio.h>
#include <stdlib.h>

#define MAX_FRAMES 3   // Maximum number of frames

void printFrames(int frames[], int numFrames) {
    for (int i = 0; i < numFrames; i++) {
        if (frames[i] == -1)
            printf("- ");
        else
            printf("%d ", frames[i]);
    }
    printf("\n");
}

int isPageInMemory(int page, int frames[], int numFrames) {
    for (int i = 0; i < numFrames; i++) {
        if (frames[i] == page)
            return 1;
    }
    return 0;
}

int getFuturePageIndex(int pages[], int numPages, int frames[], int numFrames, int currentIndex) {
    int futureIndex = -1;
    for (int i = currentIndex + 1; i < numPages; i++) {
        for (int j = 0; j < numFrames; j++) {
            if (frames[j] == pages[i]) {
                futureIndex = i;
                break;
            }
        }
        if (futureIndex != -1)
            break;
    }
    return futureIndex;
}

int getPageIndexToRemove(int pages[], int numPages, int frames[], int numFrames, int currentIndex) {
    int removeIndex = -1;
    int farthestIndex = -1;
    for (int i = 0; i < numFrames; i++) {
        int futureIndex = getFuturePageIndex(pages, numPages, frames, numFrames, currentIndex);
        if (futureIndex == -1)
            return i;
        if (futureIndex > farthestIndex) {
            farthestIndex = futureIndex;
            removeIndex = i;
        }
    }
    return removeIndex;
}

int main() {
    int pages[] = {1, 2, 3, 4, 5, 6, 1, 2, 3, 7, 8};  // Page reference string
    int numPages = sizeof(pages) / sizeof(pages[0]);

    int frames[MAX_FRAMES];   // Array to hold page frames
    int numFrames = 0;         // Number of page frames currently occupied

    // Initialize frames as empty
    for (int i = 0; i < MAX_FRAMES; i++)
        frames[i] = -1;

    // Perform Optimal page replacement
    int pageFaults = 0;
    int currentIndex = 0;   // Current index in the page reference string
    for (int i = 0; i < numPages; i++) {
        printf("Page %d: ", pages[i]);
        if (!isPageInMemory(pages[i], frames, numFrames)) {
            if (numFrames < MAX_FRAMES) {
                frames[numFrames] = pages[i];
                numFrames++;
            } else {
                int removeIndex = getPageIndexToRemove(pages, numPages, frames, numFrames, currentIndex);
                frames[removeIndex] = pages[i];
            }
            pageFaults++;
            printFrames(frames, numFrames);
        } else {
            printf("Page hit!\n");
        }
        currentIndex++;
    }

    printf("\nTotal page faults: %d\n", pageFaults);

    return 0;
}

