#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>

handle_error(char *msg)
{
    fprintf(stderr, msg);
    exit(EXIT_FAILURE);
}

typedef struct link_list
{
    char *line;
    struct link_list *Next;
} link_list;

int main(int argc, char *argv[])
{
    FILE *in = NULL, *out = NULL;
    in = stdin;
    out = stdout;

    // reverse a.txt
    if ((argc == 2) && (fopen(argv[1], "r") == NULL))
    {
        char *msg;
        sprintf(msg, "")
        
        handle_error();
    }

    // reverse a.txt b.txt
    if (argc == 3)
    {
        in = fopen(argv[1], "r");
        // 打开失败
        if (in == NULL)
        {
            fprintf(stderr, "reverse: can't open file '%s'\n", argv[1]);
            exit(EXIT_FAILURE);
        }
        out = fopen(argv[2], "w");
        if (out == NULL)
        {
            fprintf(stderr, "reverse: can't open file '%s'\n", argv[2]);
            exit(EXIT_FAILURE);
        }

        struct stat *s1 = malloc(sizeof(struct stat)), *s2 = malloc(sizeof(struct stat));
        if (s1 == NULL || s2 == NULL)
        {
            fprintf(stderr, "malloc failed\n");
            exit(EXIT_FAILURE);
        }

        if (fstat(fileno(in), s1) != 0)
        {
            free(s1);
            free(s2);
            fprintf(stderr, "reverse: fstat error\n");
            exit(EXIT_FAILURE);
        }
        if (fstat(fileno(out), s2) != 0)
        {
            free(s1);
            free(s2);
            fprintf(stderr, "reverse: fstat error\n");
            exit(EXIT_FAILURE);
        }

        // 指向同一个文件
        if (s1->st_ino == s2->st_ino)
        {
            free(s1);
            free(s2);
            fprintf(stderr, "reverse: input and output file must differ\n");
            exit(EXIT_FAILURE);
        }
        free(s1);
        free(s2);
    }

    if (argc > 3)
    {
        fprintf(stderr, "usage: reverse <input> <output>");
        exit(EXIT_FAILURE);
    }

    // 用一个链表来存放数据
    link_list *head = malloc(sizeof(link_list)), *curr = NULL, *prev = NULL;

    if (head == NULL)
    {
        fprintf(stderr, "reverse: malloc failed\n");
        exit(EXIT_FAILURE);
    }

    head->line = NULL;
    head->Next = NULL;

    curr = head;
    char *line = NULL;
    size_t linecap = 0;

    while (getline(&line, &linecap, in) > 0)
    {
        if (head->line == NULL)
        {
            if ((head->line = malloc(linecap)) == NULL)
            {
                free(head);
                fprintf(stderr, "reverse: malloc failed\n");
                exit(EXIT_FAILURE);
            }
            strcpy(head->line, line);
        }
        else
        {
            link_list *tmp = malloc(sizeof(link_list));
            if (tmp == NULL)
            {
                free(head);
                fprintf(stderr, "reverse: malloc failed\n");
                exit(EXIT_FAILURE);
            }
        }
    }

    // todo 反转链表

    return 0;
}