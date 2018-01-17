#include "mbc.h"
#include "rom.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

gb_mbc0_t *gb_mbc0_init ()
{
	gb_mbc0_t *mbc;

	mbc = malloc(sizeof(*mbc));
	if (!mbc)
		return NULL;

	mbc->type = GB_MBC0;

	return mbc;
}

void gb_mbc0_free (gb_mbc0_t *mbc)
{
	free(mbc);
}

void gb_mbc0_load_rom (gb_mbc0_t *mbc, gb_rom_t *rom)
{
	fread(mbc->mem, GB_MBC0_MEMORY_SIZE, 1, rom->file);
}

int gb_mbc0_read (gb_mbc0_t *mbc, uint16_t addr, void *buf, uint16_t sz)
{
	if (addr > (GB_MBC0_MEMORY_SIZE - sz))
		return 0;

	memcpy(buf, mbc->mem + addr, sz);

	return 1;
}

void *gb_mbc0_ref (gb_mbc0_t *mbc, uint16_t addr)
{
	return &mbc->mem[addr];
}

void gb_mbc_free (gb_mbc_t *mbc)
{
	switch (((gb_mbc_any_t *) mbc)->type) {
	case GB_MBC0:
		gb_mbc0_free(mbc);
		break;
	}
}

void gb_mbc_load_rom (gb_mbc_t *mbc, gb_rom_t *rom)
{
	switch (((gb_mbc_any_t *) mbc)->type) {
	case GB_MBC0:
		gb_mbc0_load_rom(mbc, rom);
		break;
	}
}

void *gb_mbc_ref (gb_mbc_t *mbc, uint16_t addr)
{
	void *ret;

	switch (((gb_mbc_any_t *) mbc)->type) {
	case GB_MBC0:
		ret = gb_mbc0_ref (mbc, addr);
		break;
	default:
		ret = NULL;
		break;
	}

	return ret;
}

int gb_mbc_read (gb_mbc_t *mbc, uint16_t addr, void *buf, uint16_t sz)
{
	int ret;

	switch (((gb_mbc_any_t *) mbc)->type) {
	case GB_MBC0:
		ret = gb_mbc0_read(mbc, addr, buf, sz);
		break;
	default:
		ret = 0;
	}

	return ret;
}

inline uint8_t gb_mbc_read8 (gb_mbc_t *mbc, uint16_t addr)
{
	uint8_t out;
	int ret;

	switch (((gb_mbc_any_t *) mbc)->type) {
	case GB_MBC0:
		ret = gb_mbc0_read(mbc, addr, &out, sizeof(out));
		break;
	default:
		ret = 0;
	}

	if (!ret)
		return (uint8_t) -1;

	return out;
}
