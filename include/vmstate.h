#ifndef _VM_STATE_H
#define _VM_STATE_H

#include "vmfile.h"

enum Register {
    RA = 0x00,
    RB = 0x01,
    RC = 0x02,
    RD = 0x03,
    RE = 0x04,
    RF = 0x05
};

typedef struct _VmState* VmState;

VmState vmstate_new(VmFile);
VmState vmstate_general_set(VmState, enum Register, unsigned char);
VmState vmstate_ip_inc(VmState);
/*TODO: Collaps flag functions like register functions*/
VmState vmstate_flag_equal_set_true(VmState);
VmState vmstate_flag_equal_set_false(VmState);
VmState vmstate_flag_greater_set_true(VmState);
VmState vmstate_flag_greater_set_false(VmState);
unsigned int vmstate_flag_equal_get(VmState);
unsigned int vmstate_flag_greater_get(VmState);
unsigned char vmstate_general_get(VmState, enum Register);
VmState vmstate_ip_set(VmState, unsigned int);
unsigned int vmstate_ip_get(VmState);
void vmstate_print(VmState);
void vmstate_del(VmState);


#endif
