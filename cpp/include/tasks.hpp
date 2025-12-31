#pragma once

#include <iostream>
#include <chrono>
#include <future>
#include <thread>
#include "helpers.hpp"

namespace tasks
{    

    int io_task(const unsigned short int taskId, const char* taskColor)
    {
        /* simulate I/O-bound task */
        std::cout << taskColor << "[T" << taskId << "...]" << color::x << std::flush;
        for (int i = 0; i < 10; i++)
        {
            std::cout << taskColor << taskId << color::x << std::flush;
            utils::sleep_ms(200);
        }
        std::cout << taskColor << "[T" << taskId << " done]" << color::x << std::flush;
        return 0;
    }; 
    
    
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


    int run_synchronous(bool& tasks_done)
    {
        tasks::io_task(1, color::m);
        tasks::cpu_task(3, color::g);
        tasks_done = true;
        return 0;
    }

    int run_async(bool& tasks_done)
    {
        // std::async(policy, function, arguments...)
        // std::launch::async policy foreces the task to run on a new thread
        std::future<int> res1 = std::async(std::launch::async, tasks::io_task, 1, color::m);
        utils::sleep_ms(800); // to better visualize concurrency
        std::future<int> res2 = std::async(std::launch::async, tasks::io_task, 2, color::c);
        res1.get();
        res2.get();
        tasks_done = true;
        return 0;
    }

    int run_thread(bool& tasks_done)
    {
        std::thread t1(tasks::cpu_task, 3, color::g);
        utils::sleep_ms(500);
        std::thread t2(tasks::cpu_task, 4, color::r);
        t1.join();
        t2.join();
        tasks_done = true;
        return 0;
    }

}