#include <iostream>
#include <thread>
#include <chrono>
#include <string>
#include <future>

namespace color {
    constexpr const char* x = "\033[0m";    // reset
    constexpr const char* r = "\033[31m";   // red
    constexpr const char* g = "\033[32m";   // green
    constexpr const char* y = "\033[33m";   // yellow
    constexpr const char* b = "\033[34m";   // blue
    constexpr const char* m = "\033[35m";   // magenta
    constexpr const char* c = "\033[36m";   // cyan
}

bool global_tasks_done = false;

void sleep_ms(int ms)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

int io_task(const unsigned short int taskId, const char* taskColor)
{
    /* simulate I/O-bound task */
    std::cout << taskColor << "[T" << taskId << "...]" << color::x << std::flush;
    for (int i = 0; i < 10; i++)
    {
        std::cout << taskColor << taskId << color::x << std::flush;
        sleep_ms(200);
    }
    std::cout << taskColor << "[T" << taskId << " done]" << color::x << std::flush;
    return 0;
}

int cpu_task(const unsigned short int taskId, const char* taskColor)
{
    /* simulate CPU-bound task */
    std::cout << taskColor << "[T" << taskId << "...]" << color::x << std::flush;
    int steps = 0;
    for (int i = 0; i < 1e9; i++)
    {
        if (i % static_cast<int>(1e8) == 0)
            {
                steps++;
                std::cout << taskColor << taskId << color::x << std::flush;
            }
        if (steps > 15)
            break;
    }
    std::cout << taskColor << "[T" << taskId << " done]" << color::x << std::flush;
    return 0;
}

int run_synchronous()
{
    io_task(1, color::m);
    cpu_task(3, color::g);
    global_tasks_done = true;
    return 0;
}

int run_async()
{
    // std::async(policy, function, arguments...)
    // std::launch::async policy foreces the task to run on a new thread
    std::future<int> res1 = std::async(std::launch::async, io_task, 1, color::m);
    sleep_ms(800); // to better visualize concurrency
    std::future<int> res2 = std::async(std::launch::async, io_task, 2, color::c);
    res1.get();
    res2.get();
    global_tasks_done = true;
    return 0;
}

int run_thread()
{
    std::thread t1(cpu_task, 3, color::g);
    sleep_ms(500);
    std::thread t2(cpu_task, 4, color::r);
    t1.join();
    t2.join();
    global_tasks_done = true;
    return 0;
}

int main()
{
    std::cout << "\nC++ Concurrency Demo Started\n";
    std::cout << "----------------------------\n";
    std::cout << "Enter a demo number:\n";
    std::cout << "[1] Synchronous\n";
    std::cout << "[2] Multithreading via std::async\n";
    std::cout << "[3] Multithreading via std::thread\n";
    int mode;
    std::cin >> mode;

    if (!(mode == 1 || mode == 2 || mode == 3))
    {
        std::cout << "Not recognized\n";
        return 0;
    } 

    std::cout << color::y << mode << " selected" << color::x << "\n";

    std::cout << "Tasks 1 & 2: I/O-bound\n";
    std::cout << "Tasks 3 & 4: CPU-bound\n";
    std::cout << "♥: Main's heartbeat\n";
    
    std::future<int> future_result;

    switch (mode)
    {
        case 1:
            std::cout << "\nSynchronous:\n";
            run_synchronous();
            break;
        case 2:
            std::cout << "\nMultithreading via std::async:\n";
            future_result = std::async(std::launch::async, run_async);
            break;
        case 3:
            std::cout << "\nMultithreading via std::thread:\n";
            run_thread();
            break;
        default:
            global_tasks_done = true;
            break;
    }
         
    do
    {
        sleep_ms(500);
        std::cout << "♥" << std::flush;        
    } while (!global_tasks_done);

    std::cout << "\n\nFinished\n\n";
    return 0;
}