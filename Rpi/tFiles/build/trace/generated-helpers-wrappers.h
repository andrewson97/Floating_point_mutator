/* This file is autogenerated by tracetool, do not edit. */

#define tcg_temp_new_nop(v) (v)
#define tcg_temp_free_nop(v)

static inline void gen_helper_trace_guest_mem_before_exec(TCGv_env __tcg___cpu, TCGv vaddr, uint16_t info)
{
    TCGv_env ____tcg___cpu = tcg_temp_new_nop(__tcg___cpu);
    TCGv __vaddr = tcg_temp_new_nop(vaddr);
    TCGv_i32 __info = tcg_const_i32(info);
    gen_helper_trace_guest_mem_before_exec_proxy(____tcg___cpu, __vaddr, __info);
    tcg_temp_free_nop(____tcg___cpu);
    tcg_temp_free_nop(__vaddr);
    tcg_temp_free_i32(__info);
}