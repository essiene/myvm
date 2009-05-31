#include <stdio.h>
#include <libgen.h>
#include <fcntl.h>

#include <myvm.h>

int main(int argc, char** argv)
{
    if(argc != 2) {
        printf(" Usage: %s <file>\n", basename(argv[0]));
        return 1;
    }

    char* filename = argv[1];

    int fp = open(filename, O_RDONLY);
    if(fp == -1) {
        perror("Opening source file");
        return 1;
    }

    int count = myasm_tokenize(fp);
    printf("Processed %d tokens\n", count);

    return 0;
}
