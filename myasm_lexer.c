#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

#define GETNEXT_OR_RETURN(sym, fd) \
    sym = mgetchar(sym, fd); \
    if(sym.eof) { \
        return sym.count; \
    } else


#define REPORT_EXPECT(sym, str) \
    printf("Lexical Error one Line %d, Position %d :\nExpecting: %s\nGot: %c\n", sym.linenum, sym.linepos, str, sym.val);\
    return sym.count; \
    if(1)


typedef struct {
    int count;
    char val;
    int linenum;
    int linepos;
    int eof;
} Symbol;

Symbol mgetchar(Symbol, int);
int is_space(Symbol);
int is_num(Symbol);
int is_alpha(Symbol);
int is_punctuation(Symbol, char);

int myasm_tokenize(int fd)
{
    Symbol curr = {0, -1, 1, 0, 0};

    state_1:
        GETNEXT_OR_RETURN(curr, fd);

        if(is_space(curr)) {
            goto state_1;
        }

        if(is_alpha(curr)) {
            goto state_2;
        }

        REPORT_EXPECT(curr, "WhiteSpace | [a-zA-Z]");

    state_2:
        GETNEXT_OR_RETURN(curr, fd);

        if(is_alpha(curr)) {
            goto state_2;
        }

        if(is_space(curr)) {
            goto state_3;
        }

        REPORT_EXPECT(curr, "WhiteSpace | [a-zA-Z]");

    state_3:
        GETNEXT_OR_RETURN(curr, fd);

        if(is_space(curr)) {
            goto state_3;
        }

        if(is_punctuation(curr, '$')) {
            goto state_4;
        }

        if(is_punctuation(curr, '%')) {
            goto state_6;
        }

        REPORT_EXPECT(curr, "WhiteSpace | '$' | '%'");

    state_4:
        GETNEXT_OR_RETURN(curr, fd);

        if(is_num(curr)) {
            goto state_5;
        }

        REPORT_EXPECT(curr, "[0-9]");

    state_5:
        GETNEXT_OR_RETURN(curr, fd);

        if(is_num(curr)) {
            goto state_5;
        }

        if(is_space(curr)) {
            goto state_8;
        }

        REPORT_EXPECT(curr, "WhiteSpace | [0-9]");

    state_6:
    state_8:
        goto state_1;
        

}

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
        sym.eof = 1;
        return sym;
}

int is_space(Symbol sym)
{
    if(sym.val == '\t' || sym.val == ' ' || sym.val == '\n' || sym.val == '\r') {
        return 1;
    }

    return 0;
}

int is_num(Symbol sym)
{
    if('0' <= sym.val && sym.val <= '9') {
        return 1;
    }

    return 0;
}

int is_alpha(Symbol sym) 
{
    if(('a' <= sym.val && sym.val <= 'z') || ('A' <= sym.val && sym.val <= 'Z')) {
        return 1;
    }

    return 0;
}

int is_a2f(Symbol sym)
{
    if(('a' <= sym.val && sym.val <= 'f') || ('A' <= sym.val && sym.val <= 'F')) {
        return 1;
    }

    return 0;
}

int is_punctuation(Symbol sym, char d)
{
    if(sym.val == d) {
        return 1;
    }

    return 0;
}
