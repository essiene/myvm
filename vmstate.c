#include <stdio.h>
#include <stdlib.h>
#include <myvm.h>

enum OpCode {
    LDR = 0x00,
    ADD = 0x10,
    SUB = 0x11,
    MUL = 0x12,
    DIV = 0x13,
    IN = 0x50,
    OUT = 0x51,
    ERR = 0x52
};

enum Register {
    RA = 0x00,
    RB = 0x01,
    RC = 0x02,
    RD = 0x03,
    RE = 0x04,
    RF = 0x05
};


struct _VmState {
    struct {
        enum Register a;
        enum Register b;
        enum Register c;
        enum Register d;
        enum Register e;
        enum Register f;
    } general;

    unsigned int ip;
};




VmState vmstate_new(VmFile vmfile)
{
    VmState state = calloc(sizeof(*state), 1);
    if(state == NULL) {
        vmerrno = VM_ENOCREATESTATE;
        return NULL;
    }

    state->ip = vmfile_entry_get(vmfile);

    return state;
}

void vmstate_print(VmState state)
{
    printf("Virtual Machine Registers\n");
    printf("  General: %.2x %.2x %.2x %.2x %.2x %.2x\n", \
            state->general.a, state->general.b, \
            state->general.c, state->general.d, \
            state->general.e, state->general.f);
    printf("  Instruction Pointer: %.8x\n", state->ip);
}

 void vmstate_del(VmState state)
{
    free(state);
}
