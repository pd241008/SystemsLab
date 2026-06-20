#pragma once

#include <cstdint>
#include <atomic>

namespace clipsync {

// Describes the origin of the clipboard write
enum class Origin : uint8_t {
    NONE = 0,
    WINDOWS = 1,
    WSL = 2
};

// The core structure that will be mmap'd and shared across the Windows/WSL boundary.
// It must be trivially copyable and standard layout.
struct SharedClipboardState {
    // Cross-process spinlock.
    // Note: std::atomic might require careful usage across shared memory boundaries.
    // In a POSIX/Windows shared environment, a simple atomic boolean flag works well 
    // for a spinlock, provided both architectures are x86_64.
    std::atomic<bool> spinlock;
    
    // Monotonically increasing counter to prevent cross-kernel ping-pong updates.
    uint64_t generation;
    
    // Who wrote the current content
    Origin origin;
    
    // Size of the current payload
    uint32_t payload_size;
    
    // Fixed size buffer for clipboard content (e.g., 4MB). 
    // This simplifies the memory model without needing dynamic allocation across the mmap boundary.
    static constexpr size_t MAX_PAYLOAD_SIZE = 4 * 1024 * 1024;
    char payload[MAX_PAYLOAD_SIZE];

    // Helper method to acquire the cross-process lock
    void lock() {
        while (spinlock.exchange(true, std::memory_order_acquire)) {
            // Busy wait. In production, we might want to add _mm_pause() (x86) 
            // or a small sleep to reduce CPU usage.
        }
    }

    // Helper method to release the cross-process lock
    void unlock() {
        spinlock.store(false, std::memory_order_release);
    }
};

} // namespace clipsync
