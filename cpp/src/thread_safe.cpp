#include <iostream>
#include <chrono>
#include <vector>
#include <thread>
#include <atomic>
#include <mutex>
#include <iomanip>

/*
--------------------------------
To demo and benchmark two thread-safe methods in C++:

1. With lock (Mutex)
2. Lock-free (atomic)

--------------------------------
*/


// Number of iterations and Threads
const int TOTAL_RUNS = 20'000'000;
const int THREADS = 4;


// CPU Cache Line, e.g.
// 64 bytes enough for typical x86
// 128 bytes to support most CPUs
// includeing Apple M-series
const int CACHE_LINE_SIZE = 128; 


// Counter: With lock (Slow)
// ----------------
uint64_t counter_with_lock = 0;
std::mutex mtx;

void scenario_with_lock()
{    
    for (int i = 0; i < TOTAL_RUNS / THREADS; ++i)
    {
        std::lock_guard<std::mutex> lock(mtx);
        counter_with_lock++;
    }
}


// Counter method: Lock-free (Fast)
// ----------------
// atomic for lock-free,
// and alignas to avoid False Sharing 
alignas(CACHE_LINE_SIZE) std::atomic<int> counter_lock_free{0};


void scenario_lock_free()
{
    for (int i = 0; i < TOTAL_RUNS / THREADS; ++i)
    {
        // A simple counter, 
        // hence "memory_order_relaxed" which is fast and still safe
        counter_lock_free.fetch_add(1, std::memory_order_relaxed);
    }
}

// Runner
// ----------------
void run_threads(void (*func_ptr)())
{
    std::vector<std::thread> threads;

    for (int i = 0; i < THREADS; ++i)
    {
        threads.emplace_back(func_ptr);
    }

    int i = 0;
    for (auto& t : threads)
    {
        i++;
        t.join();
        std::cout << ". " << std::flush;
    }
}

void time_it(std::string scenario, void (*func_ptr)())
{
    std::cout << scenario;
    auto start = std::chrono::high_resolution_clock::now();    
    run_threads(func_ptr);
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << " done in " 
        << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() / 1000.0 << " milliseconds\n";

}

int main()
{
    // fixed decimal places when printing time
    std::cout << std::fixed << std::setprecision(3);

    std::cout << "\nThread-Safe Benchmarking / C++ \n";
    std::cout <<   "------------------------------\n";
    std::cout << "Incrementing a counter " << TOTAL_RUNS << " times on "
        << THREADS <<  " threads:\n\n";
    
    time_it("\x1b[31m 1: With Lock (Mutex)  ", scenario_with_lock);
    time_it("\x1b[32m 2: Lock-free (Atomic) ", scenario_lock_free);

    std::cout << "\n\x1b[0mFinished\n\n";
    return 0;
}