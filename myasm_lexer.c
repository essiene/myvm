#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

typedef struct {
    int count;
    char val;
    int linenum;
    int linepos;
} Symbol;
