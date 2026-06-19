<div align="center">

# ClipSync

**A two-way, real-time clipboard sync between Windows and WSL2.**

[![Rust](https://img.shields.io/badge/rust-black?style=flat-square&logo=rust)](https://www.rust-lang.org/)
[![C++](https://img.shields.io/badge/c++-black?style=flat-square&logo=c%2B%2B)](https://isocpp.org/)
[![License: MIT](https://img.shields.io/badge/license-MIT-blue?style=flat-square)](LICENSE)
[![Status](https://img.shields.io/badge/status-building-orange?style=flat-square)]()

</div>

---

## What This Is

Copy something on Windows, it's instantly available to paste in WSL — and vice versa. No polling, no manual sync, push-based on both ends. The current clipboard state is also persisted to disk, so a restart restores the last known value instead of starting empty. 

> **Design constraint:** Bypassing standard sync loops by tagging each shared slot write with origin and monotonically increasing generation counters to prevent cross-kernel ping-pong.

---

## Architecture

This is a live mirror — one current value, kept in sync both directions — not a multi-entry clipboard history tool. The shared state isn't pure in-memory shared memory — it's backed by an mmap'd file (e.g. under `/mnt/c/Users/<you>/.clipsync/state.bin`), visible from both the Windows side and WSL side.

```text
[Windows clipboard hook] ──┐
                            ├──> Rust daemon (event-driven, both sides)
[WSL clipboard hook] ───────┘            │
                                          ▼
                          C++ memory core (spinlock-guarded
                          slot: content + generation + origin)
                                          │
                                          ▼
                          mmap'd backing file (persistence +
                          cross-boundary visibility)
                                          │
                                          ▼
                          Raylib viewer (reads state, renders
                          notepad-style UI)
```

**Core Technologies:**
- **Rust** — orchestration layer. Owns the OS event loops on both sides, handles serialization, and drives the daemon lifecycle.
- **C++** — low-level memory core. Owns the shared, mmap'd state slot and the cross-kernel spinlock guarding concurrent access. Chosen deliberately for manual memory control and as systems-programming practice.
- **Raylib** — visualization layer. A lightweight notepad-style viewer that reads clipboard state/history and renders it, decoupled from the sync hot path.

---

## Quickstart

```bash
# Clone the repository
git clone https://github.com/pd241008/clipsync.git
cd clipsync

# Build and run the daemon (Implementation pending)
cargo run --release
```

---

## Configuration

| Environment / Aspect | Description |
| -------------------- | ----------- |
| `origin` | Which side wrote it (`windows` / `wsl`) |
| `generation` | Monotonically increasing counter |
| **Windows Hooks** | `AddClipboardFormatListener` + `WM_CLIPBOARDUPDATE` |
| **WSL Hooks** | XFixes (`XFixesSelectionNotify`) on X11, or `wl-clipboard` on Wayland |

---

## Status

🚧 Early design phase — architecture and sync strategy decided, implementation not yet started.

| Component | Role | State |
|---|---|---|
| `clipsync-core` (C++) | Shared slot struct, spinlock, mmap management | 🔨 Planned |
| `clipsync-daemon-win` (Rust) | Windows clipboard listener, FFI into core | 🔨 Planned |
| `clipsync-daemon-wsl` (Rust) | WSL/X11 clipboard listener, FFI into core | 🔨 Planned |
| `clipsync-viewer` (Rust + Raylib) | Notepad-style state/history viewer | 🔨 Planned |

---

_[pd241008](https://github.com/pd241008) 
