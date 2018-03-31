#!/usr/bin/env python3
import itertools


def find_mask_and_pattern(bit_strings):
    pattern_ones = -1
    pattern_zeros = 0

    for bit_string in bit_strings:
        pattern_ones &= bit_string
        pattern_zeros |= bit_string

    mask = pattern_ones | ~pattern_zeros
    pattern = pattern_ones

    return mask, pattern


bit_strings = itertools.chain(
    range(0x78, 0x7f),
    range(0x40, 0x46),
    range(0x48, 0x4e),
    range(0x50, 0x56),
    range(0x58, 0x5e),
    range(0x60, 0x66),
    range(0x68, 0x6e),
)

if __name__ == "__main__":
    mask, pattern = find_mask_and_pattern(bit_strings)
    print("mask = {:08b}\tpattern = {:08b}".format(mask & 0xff, pattern & 0xff))
