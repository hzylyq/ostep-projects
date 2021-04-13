#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {
    FILE *fp = NULL;
    char *line = NULL;
    size_t linecap = 0;

    if (argc < 2) {
        printf("wgrep: searchterm [file ...]\n");
        exit(EXIT_FAILURE);
    }


    if (argc == 2) {
        fp = stdin;
        while (getline(&line, &linecap, fp) > 0) {
            if (strstr(line, argv[1])) {
                printf("%s", line);
            }
        }
    }

    if (argc >= 3) {
        for (int i = 2; i < argc; i++) {
            if ((fp = fopen(argv[i], "r")) == NULL) {
                printf("wgrep: cannot open file\n");
                exit(EXIT_FAILURE);
            }
            while (getline(&line, &linecap, fp) > 0) {
                if (strstr(line, argv[1])) {
                    printf("%s", line);
                }
            }
        }
    }

    fp = NULL;
    line = NULL;
}