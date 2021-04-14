#include <stdio.h>
#include <string.h>
#include <netinet/in.h>
#include <stdlib.h>

void writeFile(unsigned int count, char *oldBuff) {
    count = htonl(count);
    fwrite(&count, 4, 1, stdout);
    fwrite(oldBuff, 1, 1, stdout);
}

int main(int argc, char **argv) {
    FILE *fp = NULL;
    char buff[1];
    char oldBuff[1];

    unsigned int count = 0;

    for (size_t i = 1; i < argc; i++) {
        if ((fp = fopen(argv[i], "r")) == NULL) {
            printf("open file failed");
            exit(EXIT_FAILURE);
        }

        while (fread(buff, 1, 1, fp) > 0) {
            if (strncmp(buff, oldBuff, 1) == 0) {
                count++;
            } else {
                if (oldBuff[0] != '\0') {
                    writeFile(count, oldBuff);
                } else {
                    count = 1;
                    strcpy(oldBuff, buff);
                }
            }
        }

        fclose(fp);
    }


    writeFile(count, oldBuff);
}