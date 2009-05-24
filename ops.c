#include <stdio.h>
#include <unistd.h>
#include <myvm.h>


VmState op_ldr(VmState state, VmInst inst)
{
    enum Register target = vminst_target_get(inst);
    state = vmstate_general_set(state, target, vminst_source_get(inst));

    state = vmstate_ip_inc(state);
    return state;
}


VmState op_add(VmState state, VmInst inst)
{
    enum Register target = vminst_target_get(inst);
    enum Register source = vminst_source_get(inst);

    unsigned char newval = vmstate_general_get(state, target) + vmstate_general_get(state, source);
    state = vmstate_general_set(state, target, newval);

    state = vmstate_ip_inc(state);
    return state;
}


VmState op_sub(VmState state, VmInst inst)
{
    enum Register target = vminst_target_get(inst);
    enum Register source = vminst_source_get(inst);

    unsigned char newval = vmstate_general_get(state, target) - vmstate_general_get(state, source);
    state = vmstate_general_set(state, target, newval);

    state = vmstate_ip_inc(state);
    return state;
}

VmState op_mul(VmState state, VmInst inst)
{
    enum Register target = vminst_target_get(inst);
    enum Register source = vminst_source_get(inst);

    unsigned char newval = vmstate_general_get(state, target) * vmstate_general_get(state, source);
    state = vmstate_general_set(state, target, newval);

    state = vmstate_ip_inc(state);
    return state;
}


VmState op_div(VmState state, VmInst inst)
{
    enum Register target = vminst_target_get(inst);
    enum Register source = vminst_source_get(inst);

    unsigned char newval = vmstate_general_get(state, target) / vmstate_general_get(state, source);
    state = vmstate_general_set(state, target, newval);

    state = vmstate_ip_inc(state);
    return state;
}

VmState op_in(VmState state, VmInst inst)
{
    int n;
    printf("[myvm <input>] $ ");
    scanf("%d", &n);
    state = vmstate_general_set(state, vminst_source_get(inst), (unsigned char) n);
    state = vmstate_ip_inc(state);
    return state;
}

VmState op_out(VmState state, VmInst inst)
{
    enum Register reg = vmstate_general_get(state, vminst_source_get(inst));

    printf("%d\n", reg);
    state = vmstate_ip_inc(state);
    return state;
}

VmState op_err(VmState state, VmInst inst)
{
    write(2, "%d\n", vmstate_general_get(state, vminst_source_get(inst)));
    state = vmstate_ip_inc(state);
    return state;
}

VmState op_cmp(VmState state, VmInst inst)
{
    enum Register source = vminst_source_get(inst);
    enum Register target = vminst_target_get(inst);

    unsigned char source_value = vmstate_general_get(state, source);
    unsigned char target_value = vmstate_general_get(state, target);

    if(source_value == target_value) {
        state = vmstate_flag_equal_set_true(state);
        state = vmstate_flag_greater_set_false(state);
        goto CMP_OK;
    }

    state = vmstate_flag_equal_set_false(state);

    if(source_value > target_value) {
        state = vmstate_flag_greater_set_true(state);
        goto CMP_OK;
    }

    state = vmstate_flag_greater_set_false(state);

CMP_OK:
    state = vmstate_ip_inc(state);
    return state;
}

VmState op_jmp(VmState state, VmInst inst)
{
    unsigned int addr = vminst_source_get(inst);

    state = vmstate_ip_set(state, addr);
    return state;

}

VmState op_jpe(VmState state, VmInst inst)
{
    unsigned int addr = vminst_source_get(inst);

    if(vmstate_flag_equal_get(state) == 0x0) {
        state = vmstate_ip_inc(state);
        return state;
    }

    state = vmstate_ip_set(state, addr);
    return state;

}

VmState op_inc(VmState state, VmInst inst)
{
    enum Register reg = vminst_source_get(inst);
    unsigned char val = vmstate_general_get(state, reg);

    val += 1;

    state = vmstate_general_set(state, reg, val);
    state = vmstate_ip_inc(state);
    return state;
}
