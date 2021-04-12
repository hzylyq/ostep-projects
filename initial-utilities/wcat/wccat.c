#include <stdio.h>

int main(int argc, char *argv) {
    if (argc < 2) {
        return 0;
    }

    f := fopen(&argv[1], "r");
    if (f == NULL) {
        return 0;
    }
}
