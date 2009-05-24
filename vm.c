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

struct _Vm {
    VmFile file;
    VmState state;
};

static VmState vm_exec(VmState, VmInst);

Vm vm_new(VmFile file, VmState state)
{
    Vm vm = calloc(1, sizeof(*vm));
    if(vm == NULL) {
        vmerrno = VM_EVMCREATEERR;
        return NULL;
    }

    vm->file = file;
    vm->state = state;

    return vm;

}

Vm vm_start(Vm vm)
{
    while(1) {
        unsigned int next_addr = vmstate_ip_get(vm->state);

        VmInst inst = vmfile_inst_fetch(vm->file, next_addr);
        if(inst == NULL) {
            break;
        }

        vm->state = vm_exec(vm->state, inst);
    }

    return vm;
}

void vm_del(Vm vm)
{
    free(vm);
}


/* Private Funcs */

VmState vm_exec(VmState state, VmInst inst)
{
    switch(vminst_opcode_get(inst)) {
        case LDR: 
            state = op_ldr(state, inst);break;
        case ADD:
            state = op_add(state, inst);break;
        case SUB:
            state = op_sub(state, inst);break;
        case MUL:
            state = op_mul(state, inst);break;
        case DIV:
            state = op_div(state, inst);break;
        case IN:
            state = op_in(state, inst);break;
        case OUT:
            state = op_out(state, inst);break;
        case ERR:
            state = op_err(state, inst);break;
        default: break;
    }

    /*vmstate_print(state);*/
    return state;
}
