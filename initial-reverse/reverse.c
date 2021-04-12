#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>

#define handle_error(msg)   \
do {                        \
    fprintf(stderr, msg);   \
    exit(EXIT_FAILURE);     \
} while(0)                  \


typedef struct link_list {
    char *line;
    struct link_list *Next;
} link_list;

int main(int argc, char *argv[]) {
    FILE *in = NULL, *out = NULL;
    in = stdin;
    out = stdout;

    // reverse a.txt
    if ((argc == 2) && (fopen(argv[1], "r") == NULL)) {
        fprintf(stderr, "reverse: cannot open file '%s'\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    // reverse a.txt b.txt
    if (argc == 3) {
        // 打开失败
        if ((in = fopen(argv[1], "r")) == NULL) {
            fprintf(stderr, "reverse: cannot open file '%s'\n", argv[1]);
            exit(EXIT_FAILURE);
        }

        if ((out = fopen(argv[2], "w")) == NULL) {
            fprintf(stderr, "reverse: cannot open file '%s'\n", argv[2]);
            exit(EXIT_FAILURE);
        }

        struct stat sb1, sb2;

        if ((fstat(fileno(in), &sb1) != 0) || (fstat(fileno(out), &sb2) != 0)) {
            handle_error("reverse: fstat error\n");
        }

        // 指向同一个文件
        if (sb1.st_ino == sb2.st_ino) {
            handle_error("reverse: input and output file must differ\n");
        }
    }

    if (argc > 3) {
        handle_error("usage: reverse <input> <output>\n");
    }

    // 用一个链表来存放数据
    link_list *head = NULL;
    char *line = NULL;
    size_t linecap = 0;

    //
    while (getline(&line, &linecap, in) != -1) {
        link_list *node = malloc(sizeof(link_list));
        if (node == NULL) {
            handle_error("reverse: malloc failed\n");
        }
        if ((node->line = strdup(line)) == NULL) {
            handle_error("reverse: strdup failed\n");
        }

        node->Next = head;
        head = node;
    }

    // print reversed lines
    while (head != NULL) {
        link_list *tmp = head;
        fprintf(out, "%s", head->line);
        head = head->Next;
        free(tmp->line);
        free(tmp);
    }

    fclose(in);
    fclose(out);

    return 0;
}