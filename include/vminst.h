#ifndef _VM_INST_H
#define _VM_INST_H

typedef struct _VmInst* VmInst;

VmInst vminst_new(int, unsigned int);
unsigned char vminst_opcode_get(VmInst);
unsigned char vminst_source_get(VmInst);
unsigned char vminst_target_get(VmInst);
void vminst_print(VmInst);
void vminst_del(VmInst);


#endif
