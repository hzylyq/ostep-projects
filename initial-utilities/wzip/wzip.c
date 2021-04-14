#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void writeFile(unsigned int count, char *oldBuff) {
    fwrite(&count, 4, 1, stdout);
    fwrite(oldBuff, 1, 1, stdout);
}

int main(int argc, char **argv) {
    FILE *fp = NULL;
    char *buff = malloc(sizeof(char) * 2);
    char *oldBuff = malloc(sizeof(char) * 2);

    unsigned int count = 1;

    if (argc < 2) {
        printf("wzip: file1 [file2 ...]\n");
        exit(EXIT_FAILURE);
    }

    for (size_t i = 1; i < argc; i++) {
        if ((fp = fopen(argv[i], "r")) == NULL) {
            printf("open file failed");
            exit(EXIT_FAILURE);
        }

        while (fread(buff, 1, 1, fp) > 0) {
            if (strncmp(buff, oldBuff, 1) == 0) {
                count++;
            } else if (oldBuff[0] != '\0') {
                writeFile(count, oldBuff);
                count = 1;
                strcpy(oldBuff, buff);
            } else {
                strcpy(oldBuff, buff);
            }
        }
    }

    writeFile(count, oldBuff);

    fclose(fp);
    free(buff);
    free(oldBuff);
    exit(EXIT_SUCCESS);
}