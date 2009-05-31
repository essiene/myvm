#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

typedef struct {
    int count;
    char val;
    int linenum;
    int linepos;
} Symbol;

Symbol mgetchar(Symbol, int);

Symbol mgetchar(Symbol sym, int fd)
{
    unsigned char c;

    ssize_t bytes = read(fd, &c, sizeof(c));
    if(bytes == -1) {
        perror("Problem reading file");
        goto problem;
    }

    if(bytes == 0) {
        printf("End of file reached\n");
        goto problem;
    }

    if(c == '\n') { /*TODO: deal properly with newline on different OSes*/
        sym.linenum += 1;
        sym.linepos = 0;
    } else {
        sym.linepos += 1;
    }

    sym.val = c;
    sym.count += 1;
    return sym;

    problem:
        sym.val = -1;
        return sym;
}
