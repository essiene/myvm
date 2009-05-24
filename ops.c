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
