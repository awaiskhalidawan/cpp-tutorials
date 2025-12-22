#include <iostream>
#include <thread>
#include <chrono>

// A structure containing different counters. The structure is aligned to cache line size which means that 
// the structure memory address will be multiple of cache line size (64). This also means that the counters
// share the SAME cache line. std::hardware_destructive_interference_size is a constant in C++ library which 
// defines the CACHE line size on the current system which is 64 bytes on modern 64-bit architectures.
struct alignas(std::hardware_destructive_interference_size) SameCacheLineCounters
{
    std::atomic<uint64_t> counter1 {0};
    std::atomic<uint64_t> counter2 {0};
};

// A structure containing different counters. The structure may or may not be be aligned to cache line size
// because alignment is not mentioned while defining the structure. Each individual counters in the structure
// are cache aligned because alignment is mentioned while defining the counters. It means that that each counter 
// share the DIFFERENT cache lines.
struct DifferentCacheLineCounters
{
    alignas(std::hardware_destructive_interference_size) std::atomic<uint64_t> counter1 {0};
    alignas(std::hardware_destructive_interference_size) std::atomic<uint64_t> counter2 {0};
};

int main()
{
    std::cout << "Demonstration of cache awareness in C++ ... " << std::endl;

    constexpr uint64_t MAX_COUNTER_VALUE = 100000000UL;

    // Incrementing the counters on same cache lines by two different threads. This will cause the false sharing
    // of cache line by the threads which will impact the performance.
    {
        std::cout << "[Scenario 1]: Incrementing counters on same cache line by two different threads ... " << std::endl;
        SameCacheLineCounters sameCacheLineCounters = {};
        const auto tp1 = std::chrono::high_resolution_clock::now();

        // Launching thread 1. This thread will increment counter1.
        std::jthread th1 = std::jthread([&sameCacheLineCounters]() -> void {
            uint64_t old_value{ 0 };

            do {
                old_value = sameCacheLineCounters.counter1.fetch_add(1, std::memory_order_relaxed);
            } while (old_value < MAX_COUNTER_VALUE);
        });

        // Launching thread 2. This thread will increment counter2.
        std::jthread th2 = std::jthread([&sameCacheLineCounters]() -> void {
            uint64_t old_value{ 0 };

            do {
                old_value = sameCacheLineCounters.counter2.fetch_add(1, std::memory_order_relaxed);
            } while (old_value < MAX_COUNTER_VALUE);
        });

        th1.join();
        th2.join();

        const auto tp2 = std::chrono::high_resolution_clock::now();
        const auto executionTime = std::chrono::duration_cast<std::chrono::milliseconds>(tp2 - tp1).count();

        std::cout << "Total execution time (ms): " << executionTime << std::endl << std::endl;
    }

    // Incrementing the counters on different cache lines by two different threads. This will result in higher
    // performance because each thread will be accessing different cache lines.
    {
        std::cout << "[Scenario 2]: Incrementing counters on different cache line by two different threads ... " << std::endl;
        DifferentCacheLineCounters differentCacheLineCounters = {};
        const auto tp1 = std::chrono::high_resolution_clock::now();

        // Launching thread 1. This thread will increment counter1.
        std::jthread th1 = std::jthread([&differentCacheLineCounters]() -> void {
            uint64_t old_value{ 0 };

            do {
                old_value = differentCacheLineCounters.counter1.fetch_add(1, std::memory_order_relaxed);
            } while (old_value < MAX_COUNTER_VALUE);
        });

        // Launching thread 2. This thread will increment counter2.
        std::jthread th2 = std::jthread([&differentCacheLineCounters]() -> void {
            uint64_t old_value{ 0 };

            do {
                old_value = differentCacheLineCounters.counter2.fetch_add(1, std::memory_order_relaxed);
            } while (old_value < MAX_COUNTER_VALUE);
        });

        th1.join();
        th2.join();

        const auto tp2 = std::chrono::high_resolution_clock::now();
        const auto executionTime = std::chrono::duration_cast<std::chrono::milliseconds>(tp2 - tp1).count();

        std::cout << "Total execution time (ms): " << executionTime << std::endl << std::endl;
    }
}

