/* SPDX-License-Identifier: Apache-2.0 */

/* Minimal linker script for RP2350 (RISC-V) */

MEMORY
{
    FLASH (rx) : ORIGIN = 0x10000000, LENGTH = 16M
    SRAM (rwx) : ORIGIN = 0x20000000, LENGTH = 520K
}

INCLUDE "base.ld"
