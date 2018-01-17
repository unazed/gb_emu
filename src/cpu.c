#include "cpu.h"
#include "instructions.h"
#include "mbc.h"
#include "rom.h"
#include <stdlib.h>

gb_instr_profile_t profiles[] = {
	(gb_instr_profile_t) {
		.instr_type = LOAD_IMM,
		.cycles = 8,
		.nargs = 1,
		.mask = 0b11000111,
		.pattern = 0b00000110
	},
	(gb_instr_profile_t) {
		.instr_type = LOAD_REG_M8,
		.cycles = 8,
		.nargs = 0,
		.mask = 0b11000000,
		.pattern = 0b01000000
	}
};

int ((*instr_jmp_tbl[256])(gb_cpu_t *, gb_mbc_t *, gb_instr_t *)) = {
	[LOAD_IMM] = gb_instr_ld_imm,
	[LOAD_REG_M8] = gb_instr_ld_reg_m8
};

gb_cpu_t *gb_cpu_init ()
{
	gb_cpu_t *cpu;
       
	cpu = malloc(sizeof(*cpu));
	if (!cpu)
		return NULL;

	gb_cpu_reset(cpu);

	return cpu;
}

void gb_cpu_free (gb_cpu_t *cpu)
{
	free(cpu);
}

void gb_cpu_reset (gb_cpu_t *cpu)
{
	cpu->pc = 0x100;
}

int gb_cpu_decode_instr (gb_cpu_t *cpu, gb_mbc_t *mbc, gb_instr_t *instr)
{
	uint8_t opcode = gb_mbc_read8(mbc, cpu->pc);
	gb_instr_profile_t *profile = NULL;
	int i;

	for (i = 0; i < (sizeof(profiles) / sizeof(*profiles)); i++) {
		if ((opcode & profiles[i].mask) == profiles[i].pattern) {
			profile = &profiles[i];
			break;
		}
	}

	if (!profile)
		return 0;

	switch (profile->nargs) {
	case 2:
		instr->op2 = gb_mbc_read8(mbc, cpu->pc + 2);
	case 1:
		instr->op1 = gb_mbc_read8(mbc, cpu->pc + 1);
		break;
	}

	instr->type = profile->instr_type;
	instr->opcode = opcode;

	return 1;
}

int gb_cpu_execute_instr (gb_cpu_t *cpu, gb_mbc_t *mbc, gb_instr_t *instr)
{
	int (*func)(gb_cpu_t *, gb_mbc_t *, gb_instr_t *);
       
	func = instr_jmp_tbl[instr->type];
	if (!func)
		return 0;
	
	return func(cpu, mbc, instr);
}
