#ifndef _MY_VM_H
#define _MY_VM_H

typedef struct _VmInst* VmInst;
typedef struct _VmFile* VmFile;
typedef struct _VmState* VmState;

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
void vmfile_inst_print(VmFile);
void vmfile_close(VmFile);
unsigned char* vmfile_header_get(VmFile);
unsigned int vmfile_version_major_get(VmFile);
unsigned int vmfile_version_minor_get(VmFile);
unsigned int vmfile_size_get(VmFile);
unsigned int vmfile_entry_get(VmFile);

VmInst vminst_new(int, unsigned int);
void vminst_print(VmInst);
void vminst_del(VmInst);

VmState vmstate_new(VmFile);
void vmstate_print(VmState);
void vmstate_del(VmState);

#endif
