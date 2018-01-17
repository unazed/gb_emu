#ifndef GB_MBC_H
#define GB_MBC_H

#include <stdint.h>
#include "rom.h"

#define GB_MBC0_MEMORY_SIZE 0xffff

typedef void gb_mbc_t;

typedef enum gb_mbc_type_t {
	GB_MBC0
} gb_mbc_type_t;

typedef struct gb_mbc_any_t {
	gb_mbc_type_t type;
} gb_mbc_any_t;

typedef struct gb_mbc0_t {
	gb_mbc_type_t type;
	uint8_t mem[GB_MBC0_MEMORY_SIZE];
} gb_mbc0_t;

gb_mbc0_t *gb_mbc0_init ();
void gb_mbc0_free (gb_mbc0_t *mbc);
void gb_mbc0_load_rom (gb_mbc0_t *mbc, gb_rom_t *rom);
int gb_mbc0_read (gb_mbc0_t *mbc, uint16_t addr, void *buf, uint16_t sz);
void *gb_mbc0_ref (gb_mbc0_t *mbc, uint16_t addr);

void gb_mbc_free (gb_mbc_t *mbc);
void gb_mbc_load_rom (gb_mbc_t *mbc, gb_rom_t *rom);

int gb_mbc_read (gb_mbc_t *mbc, uint16_t addr, void *buf, uint16_t sz);
uint8_t gb_mbc_read8 (gb_mbc_t *mbc, uint16_t addr);

void *gb_mbc_ref (gb_mbc_t *mbc, uint16_t addr);

#endif /* GB_MBC_H */
