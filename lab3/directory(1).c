#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>

int main() {
    DIR *dir;
    struct dirent *entry;
    struct stat statistics;
    long long totalSize = 0;

    dir = opendir(".");

    printf("-- DIRECTORY: .");

    while ((entry = readdir(dir)) != NULL) {
        stat(entry->d_name, &statistics);
        if (!S_ISDIR(statistics.st_mode)) {
            printf("\nName: %s\n", entry->d_name);
            printf("Size: %lld bytes\n", (long long) statistics.st_size);
            totalSize += statistics.st_size;
        }
    }

    printf("\nTotal size of files: %lld bytes\n", totalSize);

    closedir(dir);
    return 0;
}