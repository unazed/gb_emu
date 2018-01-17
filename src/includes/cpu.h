#ifndef GB_CPU_H
#define GB_CPU_H

#include <stdint.h>
#include "mbc.h"
#include "rom.h"

typedef enum gb_instr_type_t {
	LOAD_IMM, LOAD_IND, LOAD_REG_M8, LOAD_REG_M16
} gb_instr_type_t;

typedef struct gb_instr_t {
	gb_instr_type_t type;
	uint8_t opcode;
	uint8_t op1;
	uint8_t op2;
} gb_instr_t;

typedef struct gb_instr_profile_t {
	gb_instr_type_t instr_type;
	uint8_t cycles;
	uint8_t nargs;
	uint8_t mask;
	uint8_t pattern;
} gb_instr_profile_t;

typedef struct __attribute__((__packed__)) gb_cpu_t {
	union {
		struct {
			uint8_t a;
			struct {
				uint8_t z:1;
				uint8_t n:1;
				uint8_t h:1;
				uint8_t c:1;
				uint8_t unused:4;
			} f;
		};
		uint16_t af;
	};
	union {
		struct { uint8_t b; uint8_t c; };
		uint16_t bc;
	};
	union {
		struct { uint8_t d; uint8_t e; };
		uint16_t de;
	};
	union {
		struct { uint8_t h; uint8_t l; };
		uint16_t hl;
	};
	uint16_t sp;
	uint16_t pc;
} gb_cpu_t;

gb_cpu_t *gb_cpu_init ();
void gb_cpu_free (gb_cpu_t *cpu);
void gb_cpu_reset (gb_cpu_t *cpu);

int gb_cpu_decode_instr (gb_cpu_t *cpu, gb_mbc_t *mbc, gb_instr_t *instr);
int gb_cpu_execute_instr (gb_cpu_t *cpu, gb_mbc_t *mbc, gb_instr_t *instr);

static inline __attribute__((always_inline))
uint8_t *gb_cpu_reg8_mem_by_id (gb_cpu_t *cpu, gb_mbc_t *mbc, uint8_t id)
{
	uint8_t *reg_map[] = {
		NULL, &cpu->b, NULL, &cpu->c,
		NULL, &cpu->d, NULL, &cpu->e,
		NULL, &cpu->h, NULL, &cpu->l,
		NULL, gb_mbc_ref(mbc, cpu->hl), NULL, &cpu->a
	};

	return (id < (sizeof(reg_map) / sizeof(*reg_map)))
		? reg_map[id]
		: NULL;
}

#endif /* GB_CPU_H */
