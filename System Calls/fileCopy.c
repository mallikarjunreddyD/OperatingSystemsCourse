#include<stdlib.h>
#include<stdio.h>

#define BUFFER_SIZE 1024
int main() {
    char inputFileName[10];
    char outputFileName[10];
     char buffer[BUFFER_SIZE];
    size_t bytesRead;

    FILE *inFile, *outFile;
    char ch;

    printf("%s", "Enter input file name");  // I/O
    scanf("%s",inputFileName);              // I/O
    printf("%s", "Enter output file name"); // I/O
    scanf("%s",outputFileName);             // I/O

    inFile = fopen(inputFileName,"rb");     // I/O
    if (inFile == NULL) {
        printf("Error Opening File");       // I/O
        return 1;
    }

    outFile = fopen(outputFileName,"wb");   // I/O
     if (outFile == NULL) {
        printf("Error Opening/Creating File");  // I/O
    }

    while ((bytesRead = fread(buffer, 1, BUFFER_SIZE, inFile)) > 0) { // I/O
        fwrite(buffer, 1, bytesRead, outFile);                        // I/O
    }
    fclose(inFile);                                                   // I/O
    fclose(outFile);                                                  // I/O

    printf("File closed successfully");                               // I/O
    return 0;

}