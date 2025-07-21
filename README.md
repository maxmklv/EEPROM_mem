# EEPROM Memory Programming

## Overview
The purpose of this project was to analyze the memories available on the Tiva TM4C123G LaunchPad development board.  
These memories consist of **Flash**, **SRAM**, and **EEPROM**.  

---

## Memory Details

- **Flash Memory**  
  - Starts at `0x00000000`, organized in 1KB independently erasable blocks.  
  - Code and data access occur over separate buses.  
  - Below 40 MHz, access is single-cycle; above 40 MHz, the prefetch buffer fetches two 32‑bit words per cycle.  
  - Programmable write and execution protection is available.

- **EEPROM**  
  - Start address: `0x400AF000` in peripheral space.  
  - Accessible as 512 32‑bit words (32 blocks × 16 words).  
  - Built‑in wear leveling, endurance of 500K writes, and access protection per block.  
  - Interrupt support for write completion; random and sequential access: 4 cycles max per word.

- **SRAM**  
  - Starts at `0x20000000`, bit-banded to `0x22000000`.  
  - Can hold code or data; bit-band operation modifies individual bits across multiple words in one cycle.

---

## Results

- **Memory Configuration & Segment Allocation Map**  
  Shows origin addresses of Flash and SRAM, lengths, usage, and read/write status.  
  Segment allocation map indicates how memory is distributed among data, with similar origin and length details.

- **FLASH Programming**  
  - After erase: memory appears as `0xFFFFFFFF`.
  - After writing a data array: programmed values visible in memory browser.
  - Red LED indicates successful write.

- **EEPROM Programming**  
  - After erase: read array contains `0xFFFFFFFF`.
  - After writing data: read array stores the written values.
  - Blue LED indicates successful write.
