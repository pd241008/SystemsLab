# C++ Systems Programming Projects

A collection of systems programming projects in C++ — allocators, emulators, renderers, and tools built from scratch.

This repository serves as a playground for exploring low-level concepts, memory management, computer architecture, and computer graphics. It is designed to provide hands-on, built-from-scratch implementations to better understand the inner workings of complex systems. Where appropriate, projects feature real-time graphical representations using [raylib](https://www.raylib.com/).

## Current Projects

### 1. Heap Visualizer (`heapvisualizer/`)
A custom heap allocator (with `my_malloc` and `my_free`) over a fixed-size `uint8_t` array, providing an interactive, real-time graphical representation of the heap's memory layout.

**Features:**
- **Custom Memory Allocator**: Implements dynamic allocation and traverses the heap using block headers, supporting basic free, allocated block management, and memory coalescing.
- **Graphical Visualization**: 
  - **Green blocks**: Allocated memory.
  - **Gray blocks**: Freed memory.
  - **Dark Gray blocks**: Untouched/Unallocated memory space.

See the [heapvisualizer README](heapvisualizer/README.md) for more detailed instructions and controls.

## Prerequisites

To compile and run the projects in this repository, you generally need:
- A C++ compiler (like `g++` or `clang++`)
- [raylib](https://github.com/raysan5/raylib) installed on your system (for visually interactive projects).

## Expanding the Library

This project is built to grow! If you want to add a new systems programming project (e.g., a simple CPU emulator, a software rasterizer, or a new allocator type):
1. Create a new directory for your concept.
2. Write your implementation (optionally using `raylib` for visualization).
3. Update this README's **Current Projects** section to list your newly added module.
