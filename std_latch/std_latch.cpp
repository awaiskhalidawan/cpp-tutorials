#include <iostream>
#include <latch>
#include <thread>

using namespace std::literals;

int main()
{
    std::cout << "Demonstration of std::latch in C++ ... " << std::endl;

    std::latch thread_latch{ 2 };       // Creating a latch with value 2. We will use this latch to synchronize the threads.

    // Create a task which performs some action then wait for other threads before continuing.
    auto task = [&]() -> void {         

        std::cout << "Thread " << std::this_thread::get_id() << ": Starting task ... " << std::endl;

        // Waiting for some random time period to emulate task execution.
        uint16_t wait_time = std::rand() % 1000;     
        std::this_thread::sleep_for(std::chrono::milliseconds(wait_time));

        std::cout << "Thread " << std::this_thread::get_id() << ": Waiting for other thread(s) here ... " << std::endl;

        // Waiting for other thread here before conitnuing from this point onwards.
        thread_latch.arrive_and_wait();

        std::cout << "Thread " << std::this_thread::get_id() << ": All other thread(s) have arrived. Continuing task ... " << std::endl;

        wait_time = std::rand() % 1000;
        std::this_thread::sleep_for(std::chrono::milliseconds(wait_time));

        std::cout << "Thread " << std::this_thread::get_id() << ": Exiting ..." << std::endl;
    };

    auto th1 = std::thread(task);                   // Launch task on a thread.
    std::this_thread::sleep_for(1s);                // Sleep for some time period. (1 second).
    auto th2 = std::thread(task);                   // Launch task on another thread.

    th1.join();                                     // Wait for thread 1 to complete.
    th2.join();                                     // Wait for thread 2 to complete.

    return 0;
}


