#include <stdio.h>
#include <libgen.h>
#include <fcntl.h>


int main(int argc, char** argv)
{
    if(argc != 2) {
        printf(" Usage: %s <file>\n", basename(argv[0]));
        return 1;
    }

    return 0;
}
