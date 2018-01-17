#ifndef GB_INSTRUCTIONS_H
#define GB_INSTRUCTIONS_H

#include "cpu.h"
#include "mbc.h"

int gb_instr_ld_imm (gb_cpu_t *cpu, gb_mbc_t *mbc, gb_instr_t *instr);
int gb_instr_ld_reg_m8 (gb_cpu_t *cpu, gb_mbc_t *mbc, gb_instr_t *instr);

#endif /* GB_INSTRUCTIONS_H */
