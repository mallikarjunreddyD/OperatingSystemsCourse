#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *sourceFile, *destFile;
    char sourceFileName[100], destFileName[100];
    char ch;
    int pid = getpid();
    printf("Pid =%d",pid);
    // Get the source and destination file names
    printf("Enter the source file name: ");
    scanf("%s", sourceFileName);
    printf("Enter the destination file name: ");
    scanf("%s", destFileName);

    // Open the source file in read mode
    sourceFile = fopen(sourceFileName, "r");
    if (sourceFile == NULL) {
        printf("Cannot open file %s for reading.\n", sourceFileName);
        exit(EXIT_FAILURE);
    }

    // Open the destination file in write mode
    destFile = fopen(destFileName, "w");
    if (destFile == NULL) {
        printf("Cannot open file %s for writing.\n", destFileName);
        fclose(sourceFile);
        exit(EXIT_FAILURE);
    }

    // Copy the contents of the source file to the destination file
    while ((ch = fgetc(sourceFile)) != EOF) {
        fputc(ch, destFile);
    }

    printf("File copied successfully.\n");

    // Close both files
    fclose(sourceFile);
    fclose(destFile);
    sleep(60);
    return 0;
}
