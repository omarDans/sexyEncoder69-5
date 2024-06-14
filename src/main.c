#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "base64.h"

void print_help() {
    printf("Usage: sexyEncoder69-5 <arguments>\n"
            "Arguments\n"
            "------------\n"
            "-e: Option for encoding in base64\n"
            "-d: Option for decoding in base64\n"
            "-s: For inputing a string (example: sexyEncoder69-5 -e -s 'encodingSMT')\n"
            "-f: For inputing a file name (example: sexyEncoder69-5 -d -f file.txt)\n"
            "-o: For inputing the name of the output file, default: output.txt (example: sexyEncoder69-5 -d -f file.txt -o decoded.txt)\n");
}

int main(int argc, char*argv[]) {
    char *stringIn = NULL;
    char *archivo = NULL;
    char *outputFile = NULL;
    int decode = 0;
    if (argc > 1) {
        for (int i = 1; i < argc; i++){
            if (strcmp(argv[i], "-f") == 0) {
                if (i+1 < argc) {
                    archivo = argv[i+1];
                    continue;
                } else {
                    printf("No value after '-f'");
                    return -1;
                }
            } else if (strcmp(argv[i], "-s") == 0) {
                if (i+1 < argc) {
                    stringIn = argv[i+1];
                    continue;
                } else {
                    printf("No value after '-s'");
                    return -1;
                }
            } else if (strcmp(argv[i], "-o") == 0) {
                if (i+1 < argc) {
                    outputFile = argv[i+1];
                    continue;
                } else {
                    outputFile = "output.txt";
                    continue;
                }
            } else if (strcmp(argv[i], "-d") == 0) {
                decode = 1;
            }
        }
    } else {
        print_help();
        return 0;
    }
    if (archivo != NULL) {

        FILE *fh = fopen(archivo, "r");
        if (fh == NULL) {
            printf("Error: could not open file %s\n", archivo);
            return -1;
        }

        int size = 100;
        stringIn = malloc(size);
        if (stringIn == NULL) {
            printf("Error allocating memory\n");
            fclose(fh);
            return -1;
        }

        char ch;
        int i = 0;
        while ((ch = fgetc(fh)) != EOF) {
            if (i >= size) {
                size += 100;
                char *temp = realloc(stringIn, size);
                if (temp == NULL) {
                    printf("Error relocating\n");
                    return -1;
                }
                stringIn = temp;
            }
            stringIn[i++] = ch;
        }
        stringIn[i] = '\0';
        fclose(fh);
    }
    char *out;
    if (decode == 1) {
        size_t number = b64_decoded_size(stringIn);
        out = malloc(number);
        out[number] = '\0';
        size_t decodedSize = b64_decode(stringIn, out, number);
        if (decodedSize == 0) {
            printf("Something went wrong while decoding :(\n");
            return -1;
        }
        printf("Decoded: %s\n", out);
    } else {
        out = b64_encode(stringIn, strlen(stringIn));
        if (out == NULL) {
            printf("Something went wrong while encoding :(\n");
            return -1;
        }
        printf("Encoded: %s\n", out);
    }
    if (outputFile != NULL) {
        FILE *fh = fopen(outputFile, "w");
        if (fh == NULL) {
            printf("Somethig went wrong while opening the file %s\n", outputFile);
            fclose(fh);
            return -1;
        }
        fprintf(fh, "%s", out);
        fclose(fh);
        printf("%s saved!\n", outputFile);
        return 0;
    }
    return 0;
}