# C++ Visualizers

A collection of algorithm and data structure visualizers written in C++ using [raylib](https://www.raylib.com/). 

This repository aims to provide real-time graphical representations of various computer science concepts. It is designed to be easily expandable, allowing new visualization modules to be added over time.

## Current Visualizers

### 1. Heap Visualizer (`heapvisualizer/`)
A custom heap allocator (with `my_malloc`) over a fixed-size `uint8_t` array, providing a real-time graphical representation of the heap's memory layout.

**Features:**
- **Custom Memory Allocator**: Implements `my_malloc` and traverses the heap using block headers (`BlockHeader`), supporting basic free and allocated block management.
- **Graphical Visualization**: 
  - **Green blocks**: Allocated memory.
  - **Gray blocks**: Freed memory.
  - **Dark Gray blocks**: Untouched/Unallocated memory space.

## Prerequisites

To compile and run the visualizers in this project, you will need:
- A C++ compiler (like `g++` or `clang++`)
- [raylib](https://github.com/raysan5/raylib) installed on your system.

## Build and Run

*Note: The following instructions are for the Heap Visualizer. Other visualizers added in the future will follow a similar pattern or have their own specific instructions.*

1. Navigate to the specific visualizer directory:

   ```bash
   cd heapvisualizer
   ```

2. Compile the code. Assuming you are using `g++`, you can run:

   ```bash
   g++ main.cpp -lraylib -o game
   ```

3. Run the executable:

   ```bash
   ./game
   ```

4. Provide the requested allocation size (under 4KB) in the terminal when prompted. After you input the value, a raylib window will open displaying the state of the heap memory.

## Expanding the Library

This project is built to grow! If you want to add a new visualization (e.g., sorting algorithms, pathfinding, tree traversals):
1. Create a new directory for your concept (e.g., `sortingvisualizer/`).
2. Write your implementation using `raylib` for the graphics loop.
3. Update this README's **Current Visualizers** section to list your newly added module.
