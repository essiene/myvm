#ifndef _VM_H
#define _VM_H

#include "vmfile.h"
#include "vmstate.h"

typedef struct _Vm* Vm;

Vm vm_new(VmFile, VmState);
Vm vm_start(Vm);
void vm_del(Vm);

#endif
