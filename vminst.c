#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <myvm.h>

struct _VmInst {
    unsigned char opcode;
    unsigned char source;
    unsigned char target;
};

VmInst vminst_new(int fd, unsigned int pos)
{
    VmInst inst = calloc(sizeof(*inst), 1);
    if(inst == NULL) {
        vmerrno = VM_ENEWINST;
        return NULL;
    }

    ssize_t bytes = read(fd, &inst->opcode, 1);
    if(bytes != 1) {
        vmerrno = VM_EREADOPCODE;
        return NULL;
    }

    bytes = read(fd, &inst->source, 1);
    if(bytes != 1) {
        vmerrno = VM_EREADSOURCE;
        return NULL;
    }

    bytes = read(fd, &inst->target, 1);
    if(bytes != 1) {
        vmerrno = VM_EREADTARGET;
        return NULL;
    }

    return inst;
}

void vminst_print(VmInst vminst)
{
    printf("%.2X%.2X%.2X\n", vminst->opcode, vminst->source, vminst->target);
}

unsigned char vminst_opcode_get(VmInst vminst)
{
    return vminst->opcode;
}

unsigned char vminst_source_get(VmInst vminst)
{
    return vminst->source;
}

unsigned char vminst_target_get(VmInst vminst)
{
    return vminst->target;
}

void vminst_del(VmInst vminst)
{
    free(vminst);
}
