#include "cpu.h"
#include "mbc.h"
#include "rom.h"
#include <stdlib.h>
#include <stdio.h>

int
main (int argc, char **argv)
{
  gb_rom_t *rom;
  gb_rom_info_t *info;
  gb_cpu_t *cpu;
  gb_mbc_t *mbc;
  gb_instr_t instr;
  char *path;

  if (argc < 2)
    {
      fprintf (stderr, "Usage: %s <rom_path>\n", argv[0]);
      return EXIT_FAILURE;
    }

  path = argv[1];

  /* load rom */
  rom = gb_rom_load (path);
  if (!rom)
    {
      fprintf (stderr, "Could not load rom!\n");
      return EXIT_FAILURE;
    }

  info = rom->info;

  /* load cpu */
  cpu = gb_cpu_init ();
  if (!cpu)
    {
      fprintf (stderr, "Could not init cpu!\n");
      gb_rom_free (rom);
      return EXIT_FAILURE;
    }

  /* load mbc */
  mbc = (gb_mbc_t *) gb_mbc0_init ();
  if (!mbc)
    {
      fprintf (stderr, "Could not init mbc!\n");
      gb_rom_free (rom);
      gb_cpu_free (cpu);
    }

  gb_mbc_load_rom (mbc, rom);

  puts ("--- Start Rom Info ---");
  printf ("Entry: 0x%04x\n", (int) info->entry);
  printf ("Title: %s\n", (char *) info->title);
  printf ("Manufacturer: %s\n", (char *) info->manufacturer);
  printf ("Licensee: %s\n", (char *) info->licensee);
  printf ("Cartridge Type: %02x\n", info->mbc_type);
  printf ("ROM Size: %02x\n", info->rom_size);
  printf ("RAM Size: %02x\n", info->ram_size);
  puts ("--- End Rom Info ---");

  while (gb_cpu_decode_instr (cpu, mbc, &instr) > 0)
    gb_cpu_execute_instr (cpu, mbc, &instr);

  gb_cpu_free (cpu);
  gb_mbc_free (mbc);
  gb_rom_free (rom);

  return EXIT_SUCCESS;
}
