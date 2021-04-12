#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#define BufferSize 1024

int main(int argc, char **argv) {
    FILE *fp;
    char buf[BufferSize];

    for (int i = 1; i < argc; i++) {
        if ((fp = fopen(argv[i], "r")) == NULL) {
            printf("wcat: cannot open file\n");
            exit(EXIT_FAILURE);
        }

        while (fgets(buf, BufferSize, fp)) {
            printf("%s", buf);
        }
        errno = 0;
        if (fclose(fp) != 0) {
            strerror(errno);
            exit(EXIT_FAILURE);
        }
    }
}
