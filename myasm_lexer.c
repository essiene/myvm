#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

#define GETNEXT_OR_RETURN(sd, fd) \
    sd = mgetchar(sd, fd); \
    if(sd.eof) { \
        return sd.count; \
    } else


#define REPORT_EXPECT(sd, str) \
    printf("Lexical Error one Line %d, Position %d :\nExpecting: %s\nGot: '%c'\n", sd.linenum, sd.linepos, str, sd.val);\
    return sd.count; \
    if(1)


typedef struct {
    int count;
    char val;
    int linenum;
    int linepos;
    int eof;
} StateData;

StateData mgetchar(StateData, int);
int is_space(StateData);
int is_num(StateData);
int is_alpha(StateData);
int is_a2f(StateData);
int is_punctuation(StateData, char);

int myasm_tokenize(int fd)
{
    StateData curr = {0, -1, 1, 0, 0};

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

        if(is_punctuation(curr, ';')) {
            goto state_1;
        }

        REPORT_EXPECT(curr, "WhiteSpace | [0-9] | ';'");

    state_6:
        GETNEXT_OR_RETURN(curr, fd);

        if(is_a2f(curr)) {
            goto state_7;
        }

        REPORT_EXPECT(curr, "[a-fA-F]");

    state_7:
        GETNEXT_OR_RETURN(curr, fd);

        if(is_space(curr)) {
            goto state_8;
        }

        if(is_punctuation(curr, ';')) {
            goto state_1;
        }

        REPORT_EXPECT(curr, "WhiteSpace | ';'");

    state_8:
        GETNEXT_OR_RETURN(curr, fd);

        if(is_space(curr)) {
            goto state_8;
        }

        if(is_punctuation(curr, ';')) {
            goto state_1;
        }

        if(is_punctuation(curr, '$')) {
            goto state_9;
        }

        if(is_punctuation(curr, '%')) {
            goto state_11;
        }

        REPORT_EXPECT(curr, "WhiteSpace | ';' | '$' | '%'");

    state_9:
        GETNEXT_OR_RETURN(curr, fd);

        if(is_num(curr)) {
            goto state_10;
        }

        REPORT_EXPECT(curr, "[0-9]");

    state_10:
        GETNEXT_OR_RETURN(curr, fd);

        if(is_num(curr)) {
            goto state_10;
        }

        if(is_space(curr)) {
            goto state_13;
        }

        if(is_punctuation(curr, ';')) {
            goto state_1;
        }

        REPORT_EXPECT(curr, "WhiteSpace | [0-9] | ';'");

    state_11:
        GETNEXT_OR_RETURN(curr, fd);

        if(is_a2f(curr)) {
            goto state_12;
        }

        REPORT_EXPECT(curr, "[a-fA-F]");

    state_12:
        GETNEXT_OR_RETURN(curr, fd);

        if(is_space(curr)) {
            goto state_13;
        }

        if(is_punctuation(curr, ';')) {
            goto state_1;
        }

        REPORT_EXPECT(curr, "Whitespace | ';'");

    state_13:
        GETNEXT_OR_RETURN(curr, fd);

        if(is_space(curr)) {
            goto state_13;
        }

        if(is_punctuation(curr, ';')) {
            goto state_1;
        }

        REPORT_EXPECT(curr, "Whitespace | ';'");
}

StateData mgetchar(StateData sd, int fd)
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
        sd.linenum += 1;
        sd.linepos = 0;
    } else {
        sd.linepos += 1;
    }

    sd.val = c;
    sd.count += 1;
    return sd;

    problem:
        sd.eof = 1;
        return sd;
}

int is_space(StateData sd)
{
    if(sd.val == '\t' || sd.val == ' ' || sd.val == '\n' || sd.val == '\r') {
        return 1;
    }

    return 0;
}

int is_num(StateData sd)
{
    if('0' <= sd.val && sd.val <= '9') {
        return 1;
    }

    return 0;
}

int is_alpha(StateData sd) 
{
    if(('a' <= sd.val && sd.val <= 'z') || ('A' <= sd.val && sd.val <= 'Z')) {
        return 1;
    }

    return 0;
}

int is_a2f(StateData sd)
{
    if(('a' <= sd.val && sd.val <= 'f') || ('A' <= sd.val && sd.val <= 'F')) {
        return 1;
    }

    return 0;
}

int is_punctuation(StateData sd, char d)
{
    if(sd.val == d) {
        return 1;
    }

    return 0;
}
