#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>

void remove_directory(const char* path) {
    DIR* dir = opendir(path);
    struct dirent* entry;

    if (!dir) {
        perror("opendir");
        return;
    }

    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        char* child_path = malloc(strlen(path) + strlen(entry->d_name) + 2);
        sprintf(child_path, "%s/%s", path, entry->d_name);

        if (entry->d_type == DT_DIR) {
            remove_directory(child_path);
        } else {
            if (unlink(child_path) != 0) {
                perror("unlink");
            }
        }

        free(child_path);
    }

    closedir(dir);

    if (rmdir(path) != 0) {
        perror("rmdir");
    }
}

int main() {
    const char* directory_path = "/path/to/directory";

    remove_directory(directory_path);

    return 0;
}
