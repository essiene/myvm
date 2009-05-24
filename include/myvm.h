#ifndef _MY_VM_H
#define _MY_VM_H

#include "vminst.h"
#include "vmfile.h"
#include "vmstate.h"
#include "ops.h"
#include "vm.h"


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
    VM_ENOCREATESTATE,
    VM_EVMCREATEERR
};


extern enum VmErrno vmerrno;

#endif
