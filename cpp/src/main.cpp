#include <iostream>
#include <future>
#include "tasks.hpp"
#include "helpers.hpp"

int main()
{
    bool global_tasks_done = false;
    
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
            tasks::run_synchronous(global_tasks_done);
            break;
        case 2:
            std::cout << "\nMultithreading via std::async:\n";
            future_result = std::async(std::launch::async, tasks::run_async, std::ref(global_tasks_done));
            break;
        case 3:
            std::cout << "\nMultithreading via std::thread:\n";
            tasks::run_thread(global_tasks_done);
            break;
        default:
            global_tasks_done = true;
            break;
    }
         
    do
    {
        utils::sleep_ms(500);
        std::cout << "♥" << std::flush;        
    } while (!global_tasks_done);

    std::cout << "\n\nFinished\n\n";
    return 0;
}