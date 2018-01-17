#ifndef GB_CARTRIDGE_H
#define GB_CARTRIDGE_H

#include <stdint.h>
#include <stdio.h>

#define GB_LOGO_SIZE 0x30
#define GB_TITLE_SIZE 0x0c
#define GB_MANUFACTURER_SIZE 0x04
#define GB_LICENSEE_SIZE 0x02

typedef struct __attribute__((__packed__)) gb_rom_info_t {
	uint32_t entry;
	uint8_t logo[GB_LOGO_SIZE];
	uint8_t title[GB_TITLE_SIZE];
	uint8_t manufacturer[GB_MANUFACTURER_SIZE];
	uint8_t cgb_flag;
	uint8_t licensee[GB_LICENSEE_SIZE];
	uint8_t sgb_flag;
	uint8_t mbc_type;
	uint8_t rom_size;
	uint8_t ram_size;
	uint8_t destination;
	uint8_t licensee_code;
	uint8_t version;
	uint8_t checksum_hdr;
	uint8_t checksum_gbl;
} gb_rom_info_t;

typedef struct gb_rom_t {
	gb_rom_info_t *info;
	FILE *file;
} gb_rom_t;

gb_rom_t *gb_rom_load (char *path);
void gb_rom_free (gb_rom_t *rom);

#endif /* GB_CARTRIDGE_H */

