# Heap Visualizer

An interactive heap allocator visualizer written in C++ using [raylib](https://www.raylib.com/). This project demonstrates how a custom memory allocator manages a fixed-size memory pool in real-time.

## Overview

The `heapvisualizer` implements a basic custom allocator (`my_malloc` and `my_free`) operating over a static 4KB memory array (`uint8_t heap[4096]`). It uses block headers (a linked list approach) to track memory chunks, supporting allocation, deallocation, and basic memory coalescing.

The raylib window provides a graphical representation of the heap's layout:
- **Green Blocks**: Actively allocated memory.
- **Gray Blocks**: Freed memory that is available for reuse.
- **Dark Gray Blocks**: Untouched/Unallocated memory space at the end of the heap.

## Controls

Once the visualizer is running, you can interact with the heap using the following keyboard controls:

- **`A`**: Allocate memory (allocates a fixed 128-byte block and pushes it to an allocation stack).
- **`F`**: Free memory (pops the last allocation from the stack and marks it as free).
- **`R`**: Reset the heap (clears the entire memory pool and resets the allocator).

## Prerequisites

- A C++ compiler (e.g., `g++` or `clang++`)
- [raylib](https://github.com/raysan5/raylib) installed on your system.

## Build and Run

1. Navigate to the visualizer directory:
   ```bash
   cd heapvisualizer
   ```

2. Compile the code. Assuming you are using `g++`, you can run:
   ```bash
   g++ main.cpp -lraylib -o visualizer
   ```

3. Run the executable:
   ```bash
   ./visualizer
   ```

A raylib window will open displaying the state of the heap memory. You can then start interacting with the heap allocator using the controls listed above.
