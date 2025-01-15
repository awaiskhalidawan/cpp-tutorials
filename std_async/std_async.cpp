#include <iostream>
#include <future>
#include <thread>
#include <vector>

using namespace std::literals;

uint32_t doSomeWork()
{
    std::cout << "Worker Thread (" << std::this_thread::get_id() << ") Starting work ... " << std::endl;

    for (uint16_t i = 0; i < 10; i++) {
        std::cout << "Worker Thread (" << std::this_thread::get_id() << ") Doing work ... " << std::endl;
        std::this_thread::sleep_for(500ms);
    }
    
    std::cout << "Worker Thread (" << std::this_thread::get_id() << ") Completed work ... " << std::endl;

    // Return some value.
    return 4;
}

int main()
{
    std::cout << "Demonstration of std::async in C++" << std::endl << std::endl;

    // Launch a task on separate thread. (Launch policy: async)
    std::cout << "Main thread (" << std::this_thread::get_id() <<"): Launching task with launch policy 'async'. " << std::endl;

    std::future<uint32_t> res1 = std::async(std::launch::async, doSomeWork);

    // Wait for the task to complete. The value returned by the task will be obtained via 'get' function of std::future.
    uint32_t ret_val = res1.get();

    // Print the result returned by the task.
    std::cout << "Main thread (" << std::this_thread::get_id() << "): Async task returned value: " << ret_val << std::endl << std::endl;

    std::this_thread::sleep_for(1000ms);

    // Launch a task on the same thread i.e. main thread. (Launch policy: deferred)
    std::cout << "Main thread (" << std::this_thread::get_id() << "): Launching task with launch policy 'deferred'. " << std::endl;

    std::future<uint32_t> res2 = std::async(std::launch::deferred, doSomeWork);

    // Wait for the task to complete. The value returned by the task will be obtained via 'get' function of std::future.
    ret_val = res2.get();

    // Print the result returned by the task.
    std::cout << "Main thread (" << std::this_thread::get_id() << "): Async task returned value: " << ret_val << std::endl << std::endl;

    return 0;
}


