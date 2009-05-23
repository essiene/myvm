#ifndef _MY_VM_H
#define _MY_VM_H

typedef struct _VmInst* VmInst;
typedef struct _VmFile* VmFile;
typedef struct _VmState* VmState;

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

enum VmErrno {
    VM_EOK,
    VM_ENOMEM,
    VM_ENOHEADER,
    VM_ENOVERSION,
    VM_ENOSIZE,
    VM_ENOENTRY,
    VM_EINVALID_STRUCT,
    VM_ENOUNUSED,
    VM_ENEWINST,
    VM_EREADOPCODE,
    VM_EREADSOURCE,
    VM_EREADTARGET,
    VM_ENOCREATESTATE
};


extern enum VmErrno vmerrno;

VmFile vmfile_open(int);
VmInst vmfile_inst_fetch(VmFile, unsigned int);
unsigned char* vmfile_header_get(VmFile);
unsigned int vmfile_version_major_get(VmFile);
unsigned int vmfile_version_minor_get(VmFile);
unsigned int vmfile_size_get(VmFile);
unsigned int vmfile_entry_get(VmFile);
void vmfile_inst_print(VmFile);
void vmfile_close(VmFile);

VmInst vminst_new(int, unsigned int);
unsigned char vminst_opcode_get(VmInst);
unsigned char vminst_source_get(VmInst);
unsigned char vminst_target_get(VmInst);
void vminst_print(VmInst);
void vminst_del(VmInst);

VmState vmstate_new(VmFile);
VmState vmstate_general_set(VmState, enum Register, unsigned char);
VmState vmstate_ip_inc(VmState);
unsigned char vmstate_general_get(VmState, enum Register);
unsigned int vmstate_ip_get(VmState);
void vmstate_print(VmState);
void vmstate_del(VmState);

#endif
