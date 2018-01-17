#include "rom.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

gb_rom_t *gb_rom_load (char *path)
{
	gb_rom_t *rom;
	gb_rom_info_t *info;
	FILE *f;

	rom = malloc(sizeof(*rom));
	if (!rom)
		return NULL;

	info = malloc(sizeof(*info));
	if (!info) {
		free(rom);
		return NULL;
	}

	/* load file metadata */
	f = fopen(path, "r");
	if (!f) {
		free(rom);
		free(info);
		return NULL;
	}

	fseek(f, 0x100, SEEK_SET);
	fread(info, sizeof(*info), 1, f);
	
	rom->file = f;
	rom->info = info;

	return rom;
}

void gb_rom_free (gb_rom_t *rom)
{
	fclose(rom->file);
	free(rom->info);
	free(rom);
}
