#include <stdio.h>
#include <stdlib.h>

struct link_list
{
   Next *link_list
};


int main(int argc, char *argv[]) {
   FILE *in = NULL, *out = NULL;
   in = stdin;
   out = stdout;

    // reverse a.txt
   if (argc == 2) {
       in = fopen(argv[1], "r");
       // 打开失败
       if (in == NULL) {
           fprintf(stderr, "reverse: can't open file '%s'\n", argv[1]);
           exit(EXIT_FAILURE);
       }
   }

   // reverse a.txt b.txt
   if (argc == 3) {
        in = fopen(argv[1], "r");
       // 打开失败
       if (in == NULL) {
           fprintf(stderr, "reverse: can't open file '%s'\n", argv[1]);
           exit(EXIT_FAILURE);
       }
       out = fopen(argv[2], "w");
       if (out == NULL) {
           fprintf(stderr, "reverse: can't open file '%s'\n", argv[2]);
           exit(EXIT_FAILURE);
       }
   }

   if (argc > 3) {
        fprintf(stderr, "usage: reverse <input> <output>");
        exit(EXIT_FAILURE);
   }

   return 0;
}