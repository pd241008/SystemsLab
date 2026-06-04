# CHIP-8 Emulator

A CHIP-8 emulator and interpreter written in C++ using [raylib](https://www.raylib.com/). This project demonstrates how a simple virtual machine from 1977 operates.

## Overview

CHIP-8 is a virtual machine from 1977. It has:
- 4KB of memory
- 16 general-purpose registers (V0–VF)
- A 64×32 monochrome display
- A stack (for subroutine calls)
- 35 opcodes

You write an interpreter that reads a `.ch8` ROM file, decodes each 2-byte instruction, and executes it — rendering output with Raylib.

### What CHIP-8 will teach you that this project didn't:
- Bitwise operations (`&`, `|`, `^`, `>>`, `<<`) on raw binary data
- Opcode decoding — extracting nibbles from 2-byte instructions
- How a fetch-decode-execute cycle actually works
- Memory-mapped display buffer
- How real VMs like JVM and V8 are structured at their core

## Prerequisites

- A C++ compiler (e.g., `g++` or `clang++`)
- [raylib](https://github.com/raysan5/raylib) installed on your system.

## Build and Run

1. Navigate to the emulator directory:
   ```bash
   cd chipemulator
   ```

2. Compile the code. Assuming you are using `g++`, you can run:
   ```bash
   g++ main.cpp -lraylib -o chipemulator
   ```

3. Run the executable:
   ```bash
   ./chipemulator
   ```
