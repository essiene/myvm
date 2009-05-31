#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

#define LEXEME_SIZE_MAX 256

#define GETNEXT_OR_RETURN(sd, fd) \
    sd = get_next(sd, fd); \
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
    int tokens;
    int lexeme_index;
    char lexeme[LEXEME_SIZE_MAX];
} StateData;

StateData get_next(StateData, int);
int is_space(StateData);
int is_num(StateData);
int is_alpha(StateData);
int is_a2f(StateData);
int is_punctuation(StateData, char);

int myasm_tokenize(int fd)
{
    StateData sdata = {0, -1, 1, 0, 0, 0, 0};

    state_1:
        sdata.lexeme_index = 0;
        sdata.lexeme[sdata.lexeme_index] = '\0';

        GETNEXT_OR_RETURN(sdata, fd);

        if(is_space(sdata)) {
            goto state_1;
        }

        if(is_alpha(sdata)) {
            goto state_2;
        }

        REPORT_EXPECT(sdata, "WhiteSpace | [a-zA-Z]");

    state_2:
        GETNEXT_OR_RETURN(sdata, fd);

        if(is_alpha(sdata)) {
            goto state_2;
        }

        if(is_space(sdata)) {
            goto state_3_extract_opcode;
        }

        REPORT_EXPECT(sdata, "WhiteSpace | [a-zA-Z]");

    state_3_extract_opcode:
        sdata.lexeme[sdata.lexeme_index] = '\0';
        printf("OPCODE: %s\n", sdata.lexeme);
        sdata.lexeme_index = 0;
        sdata.lexeme[sdata.lexeme_index] = '\0';
        sdata.tokens += 1;
        goto state_3;

    state_3:
        GETNEXT_OR_RETURN(sdata, fd);

        if(is_space(sdata)) {
            goto state_3;
        }

        if(is_punctuation(sdata, '$')) {
            goto state_4;
        }

        if(is_punctuation(sdata, '%')) {
            goto state_6;
        }

        REPORT_EXPECT(sdata, "WhiteSpace | '$' | '%'");

    state_4:
        GETNEXT_OR_RETURN(sdata, fd);

        if(is_num(sdata)) {
            goto state_5;
        }

        REPORT_EXPECT(sdata, "[0-9]");

    state_5:
        GETNEXT_OR_RETURN(sdata, fd);

        if(is_num(sdata)) {
            goto state_5;
        }

        if(is_space(sdata)) {
            goto state_8_extract_opcode;
        }

        if(is_punctuation(sdata, ';')) {
            goto state_source_only;
        }

        REPORT_EXPECT(sdata, "WhiteSpace | [0-9] | ';'");

    state_6:
        GETNEXT_OR_RETURN(sdata, fd);

        if(is_a2f(sdata)) {
            goto state_7;
        }

        REPORT_EXPECT(sdata, "[a-fA-F]");

    state_7:
        GETNEXT_OR_RETURN(sdata, fd);

        if(is_space(sdata)) {
            goto state_8_extract_opcode;
        }

        if(is_punctuation(sdata, ';')) {
            goto state_source_only;
        }

        REPORT_EXPECT(sdata, "WhiteSpace | ';'");

    state_8_extract_opcode:
        sdata.lexeme[sdata.lexeme_index] = '\0';
        printf("SOURCE: %s\n", sdata.lexeme+1);
        sdata.lexeme_index = 0;
        sdata.lexeme[sdata.lexeme_index] = '\0';
        sdata.tokens += 1;
        goto state_8;

    state_8:
        GETNEXT_OR_RETURN(sdata, fd);

        if(is_space(sdata)) {
            goto state_8;
        }

        if(is_punctuation(sdata, ';')) {
            goto state_source_only;
        }

        if(is_punctuation(sdata, '$')) {
            goto state_9;
        }

        if(is_punctuation(sdata, '%')) {
            goto state_11;
        }

        REPORT_EXPECT(sdata, "WhiteSpace | ';' | '$' | '%'");

    state_source_only:
        sdata.lexeme[sdata.lexeme_index-1] = '\0';
        printf("SOURCE: %s\n", sdata.lexeme+1);
        sdata.tokens += 1;
        goto state_1;


    state_9:
        GETNEXT_OR_RETURN(sdata, fd);

        if(is_num(sdata)) {
            goto state_10;
        }

        REPORT_EXPECT(sdata, "[0-9]");

    state_10:
        GETNEXT_OR_RETURN(sdata, fd);

        if(is_num(sdata)) {
            goto state_10;
        }

        if(is_space(sdata)) {
            goto state_13;
        }

        if(is_punctuation(sdata, ';')) {
            goto state_pre_1;
        }

        REPORT_EXPECT(sdata, "WhiteSpace | [0-9] | ';'");

    state_11:
        GETNEXT_OR_RETURN(sdata, fd);

        if(is_a2f(sdata)) {
            goto state_12;
        }

        REPORT_EXPECT(sdata, "[a-fA-F]");

    state_12:
        GETNEXT_OR_RETURN(sdata, fd);

        if(is_space(sdata)) {
            goto state_13;
        }

        if(is_punctuation(sdata, ';')) {
            goto state_pre_1;
        }

        REPORT_EXPECT(sdata, "Whitespace | ';'");

    state_13:
        GETNEXT_OR_RETURN(sdata, fd);

        if(is_space(sdata)) {
            goto state_13;
        }

        if(is_punctuation(sdata, ';')) {
            goto state_pre_1;
        }

        REPORT_EXPECT(sdata, "Whitespace | ';'");

    state_pre_1:
        sdata.lexeme[sdata.lexeme_index-1] = '\0';
        printf("TARGET: %s\n", sdata.lexeme+1);
        sdata.tokens += 1;
        goto state_1;
}

StateData get_next(StateData sd, int fd)
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

    sd.lexeme[sd.lexeme_index] = c;
    sd.val = c;
    sd.count += 1;
    sd.lexeme_index += 1;
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
