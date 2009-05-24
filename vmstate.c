#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <myvm.h>


struct _VmState {
    struct {
        enum Register a;
        enum Register b;
        enum Register c;
        enum Register d;
        enum Register e;
        enum Register f;
    } general;

    struct {
        unsigned int equal:1;
        unsigned int unused: 7;
    } flag;

    unsigned int ip;
};

VmState vmstate_new(VmFile vmfile)
{
    VmState state = calloc(sizeof(*state), 1);
    if(state == NULL) {
        vmerrno = VM_ENOCREATESTATE;
        return NULL;
    }

    state->general.a = 0x00;
    state->general.b = 0x00;
    state->general.c = 0x00;
    state->general.d = 0x00;
    state->general.e = 0x00;
    state->general.f = 0x00;

    state->ip = vmfile_entry_get(vmfile) - 0x10; /* remove header size to adjust for zero */
    return state;
}

unsigned char vmstate_general_get(VmState state, enum Register reg)
{
    switch(reg) {
        case RA:
            return state->general.a;
        case RB:
            return state->general.b;
        case RC:
            return state->general.c;
        case RD:
            return state->general.d;
        case RE:
            return state->general.e;
        case RF:
            return state->general.f;
    }

    return 0;
}

VmState vmstate_general_set(VmState state, enum Register reg, unsigned char data)
{
    switch(reg) {
        case RA:
            state->general.a = data;break;
        case RB:
            state->general.b = data;break;
        case RC:
            state->general.c = data;break;
        case RD:
            state->general.d = data;break;
        case RE:
            state->general.e = data;break;
        case RF:
            state->general.f = data;break;
    }

    return state;
}

unsigned int vmstate_ip_get(VmState state)
{
    return state->ip;
}

VmState vmstate_ip_inc(VmState state)
{
    state->ip += 1;
    return state;
}

VmState vmstate_flag_equal_set_true(VmState state)
{
    state->flag.equal = 0x1;
    return state;
}

VmState vmstate_flag_equal_set_false(VmState state)
{
    state->flag.equal = 0x0;
    return state;
}

unsigned int vmstate_flag_equal_get(VmState state)
{
    return state->flag.equal;
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
