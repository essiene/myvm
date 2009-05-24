#ifndef _OPS_H
#define _OPS_H

#include "vminst.h"
#include "vmstate.h"

VmState op_ldr(VmState, VmInst);
VmState op_add(VmState, VmInst);
VmState op_sub(VmState, VmInst);
VmState op_mul(VmState, VmInst);
VmState op_div(VmState, VmInst);
VmState op_in(VmState, VmInst);
VmState op_out(VmState, VmInst);
VmState op_err(VmState, VmInst);

#endif
