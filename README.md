<div align="center">

# Visualizer

**A collection of systems programming projects exploring memory management, computer architecture, and OS-level integrations.**

[![C++](https://img.shields.io/badge/c++-black?style=flat-square&logo=c%2B%2B)](https://isocpp.org/)
[![Rust](https://img.shields.io/badge/rust-black?style=flat-square&logo=rust)](https://www.rust-lang.org/)
[![Status](https://img.shields.io/badge/status-building-orange?style=flat-square)]()

</div>

---

## What This Is

This repository serves as a practical playground for exploring low-level concepts through hands-on, built-from-scratch implementations. Where appropriate, projects feature real-time graphical representations using raylib to visualize the inner workings of complex systems.

> **Design constraint:** Building raw memory allocators, virtual machine execution loops, and cross-kernel synchronization primitives from the ground up without relying on high-level abstractions.

---

## Quickstart

```bash
git clone https://github.com/pd241008/Visualizer
cd Visualizer

# Navigate to a specific project to build and run
cd chipemulator
mkdir build && cd build && cmake .. && make
./chipemulator path/to/rom.ch8
```

---

## Projects

| Project | Description | State |
| ------- | ----------- | ----- |
| **`heapvisualizer`** | Custom heap allocator (`my_malloc`/`my_free`) with interactive real-time memory visualization via raylib. | ✅ Stable |
| **`chipemulator`** | CHIP-8 virtual machine interpreter with a fetch-decode-execute loop and raylib rendering. | 🔨 Building |
| **`clipsync`** | Two-way, real-time clipboard sync between Windows and WSL2 via mmap'd state and spinlocks. | 🚧 Early Design |

---

_[pd241008](https://github.com/pd241008) · [ct-os-dev-portfolio.vercel.app](https://ct-os-dev-portfolio.vercel.app)_
