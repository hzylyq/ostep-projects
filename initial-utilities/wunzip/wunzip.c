#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>

int main(int argc, char **argv) {
    FILE *fp = NULL;

    char buff[5];
    for (size_t i = 0; i < argc; i++) {
        if ((fp = fopen(argv[i], "rb")) == NULL) {
            exit(EXIT_FAILURE);
        }

        int count = 0;
        while (fread(&count, 4, 1, fp)) {
            memset(buff, 0, sizeof(buff));
            fread(buff, 1, 1, fp);
            for (size_t j = 0; j < count; j++) {
                printf("%s", buff);
            }
        }
        fclose(fp);
    }

    return 0;
}