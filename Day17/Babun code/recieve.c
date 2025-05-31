#include <stdio.h>
#include <stdlib.h>

#define FILENAME "message.txt"
#define MAX 100

int main() {
    char buffer[MAX];

    FILE *fp = fopen(FILENAME, "r");
    if (fp == NULL) {
        perror("Error opening file for reading");
        return 1;
    }

    fgets(buffer, MAX, fp);
    fclose(fp);

    printf("Data received is: %s\n", buffer);
    return 0;
}
