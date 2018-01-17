#include "cpu.h"
#include "instructions.h"
#include "mbc.h"

int gb_instr_ld_imm (gb_cpu_t *cpu, gb_mbc_t *mbc, gb_instr_t *instr)
{
	uint8_t *reg;
       
	reg = gb_cpu_reg8_mem_by_id(cpu, mbc, (instr->opcode >> 2) & 0xf);
	if (!reg)
		return 0;

	*reg = instr->op1;
	cpu->pc += 2;

	return 1;
}

int gb_instr_ld_reg_m8 (gb_cpu_t *cpu, gb_mbc_t *mbc, gb_instr_t *instr)
{
	uint8_t dst_id = ((instr->opcode >> 2) & 0xe) | 1; /* (((instr->opcode >> 3) & 0x07) << 1) | 1; */
	uint8_t src_id = ((instr->opcode << 1) | 1) & 0xf;
	uint8_t *dst = gb_cpu_reg8_mem_by_id(cpu, mbc, dst_id);
	uint8_t *src = gb_cpu_reg8_mem_by_id(cpu, mbc, src_id);

	*dst = *src;

	return 1;
}
